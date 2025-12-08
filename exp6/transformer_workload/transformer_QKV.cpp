
/*
Simple Transformer-like attention workload for gem5-salam performance testing
File: gem5_salam_transformer_workload.c

This single-file workload performs simple Q/K/V generation and computes
scaled dot-product attention (softmax(QK^T/sqrt(d))*V) repeatedly.
The code is intentionally straightforward (no BLAS dependency) so it
behaves as a standalone user-mode binary for gem5.

Features:
 - Command-line configurable: batch, seq_len, dim, iterations
 - Measures wall-clock time per iteration using clock_gettime
 - Uses naive triple loops (easy to map to CPU/memory stress)
 - Optionally enables a lightweight block multiply (toggle with define)

Recommended sizes for gem5-salam testing:
 - Small quick test: batch=1 seq=64 dim=64 iters=5
 - Medium: batch=1 seq=256 dim=256 iters=10
 - Heavy (compute-bound): batch=1 seq=512 dim=1024 iters=5
 - Memory-bound (increase seq_len or batch): batch=4 seq=1024 dim=256 iters=3

Notes for gem5:
 - Build as a static binary if running in syscall-emulation mode (optional).
 - Use -O3 for best in-core performance; to test memory limits, reduce
optimization.

*/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* Toggle blocking multiply for alternative pattern (uncomment to enable) */
/* #define USE_BLOCKING 1 */

static inline double now_seconds() {
    struct timespec t;
    clock_gettime(CLOCK_MONOTONIC, &t);
    return t.tv_sec + t.tv_nsec * 1e-9;
}

/* simple rng */
static float frandf(unsigned *seed) {
    *seed = (*seed * 1664525u) + 1013904223u;
    return (float)(*seed & 0xFFFFFF) / (float)0x1000000;
}

/* allocate contiguous float array */
static float *allocf(size_t n) {
    float *p = (float *)aligned_alloc(64, n * sizeof(float));
    if (!p) {
        perror("aligned_alloc");
        exit(1);
    }
    return p;
}

/* softmax on row of length n: in-place */
static void softmax_inplace(float *row, int n) {
    float maxv = row[0];
    for (int i = 1; i < n; ++i)
        if (row[i] > maxv)
            maxv = row[i];
    double sum = 0.0;
    for (int i = 0; i < n; ++i) {
        row[i] = expf(row[i] - maxv);
        sum += row[i];
    }
    float inv = 1.0f / (float)sum;
    for (int i = 0; i < n; ++i)
        row[i] *= inv;
}

int main(int argc, char **argv) {
    if (argc < 5) {
        fprintf(stderr, "Usage: %s <batch> <seq_len> <dim> <iterations>\n",
                argv[0]);
        fprintf(stderr, "Example: %s 1 512 1024 10\n", argv[0]);
        return 1;
    }
    int B = atoi(argv[1]);
    int S = atoi(argv[2]);
    int D = atoi(argv[3]);
    int ITERS = atoi(argv[4]);

    if (B <= 0 || S <= 0 || D <= 0 || ITERS <= 0) {
        fprintf(stderr, "All args must be positive integers.\n");
        return 1;
    }

    printf("Transformer-like attention workload: B=%d S=%d D=%d ITERS=%d\n", B,
           S, D, ITERS);

    size_t qkv_size = (size_t)B * S * D;
    size_t scores_size = (size_t)B * S * S; /* for each batch, SxS scores */

    float *Q = allocf(qkv_size);
    float *K = allocf(qkv_size);
    float *V = allocf(qkv_size);
    float *scores = allocf(scores_size);
    float *out = allocf(qkv_size);

    /* init pseudo-random data */
    unsigned seed = 123456789;
    for (size_t i = 0; i < qkv_size; ++i) {
        Q[i] = frandf(&seed) - 0.5f;
        K[i] = frandf(&seed) - 0.5f;
        V[i] = frandf(&seed) - 0.5f;
    }

    const float scale = 1.0f / sqrtf((float)D);

    double t0 = now_seconds();

    for (int it = 0; it < ITERS; ++it) {
        /* for each batch */
        for (int b = 0; b < B; ++b) {
            float *Qb = Q + (size_t)b * S * D;
            float *Kb = K + (size_t)b * S * D;
            float *Vb = V + (size_t)b * S * D;
            float *Sb = scores + (size_t)b * S * S;
            float *Ob = out + (size_t)b * S * D;

            /* compute scores = Q * K^T  (S x D) * (D x S) => S x S */
#ifdef USE_BLOCKING
            /* Simple blocking for D to create different memory access pattern
             */
            int Bk = 32; /* block size */
            for (int i = 0; i < S; ++i) {
                float *qi = Qb + (size_t)i * D;
                for (int j = 0; j < S; ++j)
                    Sb[i * S + j] = 0.0f;
                for (int kk = 0; kk < D; kk += Bk) {
                    int kend = kk + Bk > D ? D : kk + Bk;
                    for (int j = 0; j < S; ++j) {
                        float *kj = Kb + (size_t)j * D + kk;
                        float sum = 0.0f;
                        for (int k = kk; k < kend; ++k)
                            sum += qi[k] * kj[k];
                        Sb[i * S + j] += sum;
                    }
                }
                /* scale */
                for (int j = 0; j < S; ++j)
                    Sb[i * S + j] *= scale;
                /* softmax */
                softmax_inplace(&Sb[i * S], S);
            }
#else
            for (int i = 0; i < S; ++i) {
                for (int j = 0; j < S; ++j) {
                    double sum = 0.0;
                    float *qi = Qb + (size_t)i * D;
                    float *kj = Kb + (size_t)j * D;
                    for (int k = 0; k < D; ++k)
                        sum += (double)qi[k] * (double)kj[k];
                    Sb[i * S + j] = (float)(sum * scale);
                }
                softmax_inplace(&Sb[i * S], S);
            }
#endif

            /* out = scores * V  => (S x S) * (S x D) = S x D */
            for (int i = 0; i < S; ++i) {
                float *oi = Ob + (size_t)i * D;
                /* zero initialize output row */
                for (int d = 0; d < D; ++d)
                    oi[d] = 0.0f;
                for (int j = 0; j < S; ++j) {
                    float s = Sb[i * S + j];
                    float *vj = Vb + (size_t)j * D;
                    for (int d = 0; d < D; ++d)
                        oi[d] += s * vj[d];
                }
            }

            /* a tiny post-op to avoid optimizer throwing away results */
            float check = 0.0f;
            for (size_t x = 0; x < (size_t)S * D; x += (D > 0 ? D : 1))
                check += Ob[x];
            if (check > 1e30f || check < -1e30f)
                fprintf(stderr, "overflow\n");
        }

        if ((it + 1) % 1 == 0) {
            double t = now_seconds();
            printf("iter %d done, elapsed %.6f s\n", it + 1, t - t0);
        }
    }

    double t1 = now_seconds();
    double total = t1 - t0;
    printf("Total time: %.6f s, avg per iter: %.6f s\n", total, total / ITERS);

    /* print a small checksum so outputs vary with input */
    double checksum = 0.0;
    for (size_t i = 0; i < (size_t)B * S * D; i += (D > 0 ? D : 1))
        checksum += out[i];
    printf("checksum: %.9f\n", checksum);

    free(Q);
    free(K);
    free(V);
    free(scores);
    free(out);
    return 0;
}
