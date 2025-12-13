#include "../../../common/m5ops.h"
#include "../qkv_clstr_hw_defines.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../defines.h"
#include "bench.h"
volatile uint8_t *top = (uint8_t *)(TOP + 0x00);
volatile uint32_t *val_a = (uint32_t *)(TOP + 0x01);
volatile uint32_t *val_b = (uint32_t *)(TOP + 0x09);
volatile uint32_t *val_c = (uint32_t *)(TOP + 0x11);
volatile uint32_t *val_d = (uint32_t *)(TOP + 0x019);
	



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

int __attribute__((optimize("0"))) main(void) {

//printf("1\n");
    m5_reset_stats();
//printf("2\n");
    uint32_t base = 0x80c00000;
    TYPE *m1 = (TYPE *) base;
    TYPE *m2 = (TYPE *) (base + sizeof(TYPE)*ROW*COL);
    TYPE *m3 = (TYPE *) (base + sizeof(TYPE)*2*ROW*COL);
    TYPE *m4 = (TYPE *) (base + sizeof(TYPE)*3*ROW*COL);


    volatile int count = 0;
    stage = 0;
//printf("3\n");
    random_generate(m1, m2, m3);
printf("4\n");
    *val_a = (uint32_t)(void *) m1;
    *val_b = (uint32_t)(void *) m2;
    *val_c = (uint32_t)(void *) m3;
    *val_d = (uint32_t)(void *) m4;
    *top = 0x01;
//printf("5\n");

    while (stage < 1) count++;
    printf("Job complete\n");

    m5_dump_stats();
    m5_exit();


//    uint32_t qkv_size = size_t qkv_size = (size_t)B * S * D;
//    size_t scores_size = (size_t)B * S * S; /* for each batch, SxS scores */
//
//    float *Q = allocf(qkv_size);
//    float *K = allocf(qkv_size);
//    float *V = allocf(qkv_size);
//    float *scores = allocf(scores_size);
//    float *out = allocf(qkv_size);
//
//   
//
//    const float scale = 1.0f / sqrtf((float)D);
//
//    double t0 = now_seconds();
//
//    for (int it = 0; it < ITERS; ++it) {
//        /* for each batch */
//        for (int b = 0; b < B; ++b) {
//            float *Qb = Q + (size_t)b * S * D;
//            float *Kb = K + (size_t)b * S * D;
//            float *Vb = V + (size_t)b * S * D;
//            float *Sb = scores + (size_t)b * S * S;
//            float *Ob = out + (size_t)b * S * D;
//
//            /* compute scores = Q * K^T  (S x D) * (D x S) => S x S */
//#ifdef USE_BLOCKING
//            /* Simple blocking for D to create different memory access pattern
//             */
//            int Bk = 32; /* block size */
//            for (int i = 0; i < S; ++i) {
//                float *qi = Qb + (size_t)i * D;
//                for (int j = 0; j < S; ++j)
//                    Sb[i * S + j] = 0.0f;
//                for (int kk = 0; kk < D; kk += Bk) {
//                    int kend = kk + Bk > D ? D : kk + Bk;
//                    for (int j = 0; j < S; ++j) {
//                        float *kj = Kb + (size_t)j * D + kk;
//                        float sum = 0.0f;
//                        for (int k = kk; k < kend; ++k)
//                            sum += qi[k] * kj[k];
//                        Sb[i * S + j] += sum;
//                    }
//                }
//                /* scale */
//                for (int j = 0; j < S; ++j)
//                    Sb[i * S + j] *= scale;
//                /* softmax */
//                softmax_inplace(&Sb[i * S], S);
//            }
//#else
//            for (int i = 0; i < S; ++i) {
//                for (int j = 0; j < S; ++j) {
//                    double sum = 0.0;
//                    float *qi = Qb + (size_t)i * D;
//                    float *kj = Kb + (size_t)j * D;
//                    for (int k = 0; k < D; ++k)
//                        sum += (double)qi[k] * (double)kj[k];
//                    Sb[i * S + j] = (float)(sum * scale);
//                }
//                softmax_inplace(&Sb[i * S], S);
//            }
//#endif
//
//            /* out = scores * V  => (S x S) * (S x D) = S x D */
//            for (int i = 0; i < S; ++i) {
//                float *oi = Ob + (size_t)i * D;
//                /* zero initialize output row */
//                for (int d = 0; d < D; ++d)
//                    oi[d] = 0.0f;
//                for (int j = 0; j < S; ++j) {
//                    float s = Sb[i * S + j];
//                    float *vj = Vb + (size_t)j * D;
//                    for (int d = 0; d < D; ++d)
//                        oi[d] += s * vj[d];
//                }
//            }
//
//            /* a tiny post-op to avoid optimizer throwing away results */
//            float check = 0.0f;
//            for (size_t x = 0; x < (size_t)S * D; x += (D > 0 ? D : 1))
//                check += Ob[x];
//            if (check > 1e30f || check < -1e30f)
//                fprintf(stderr, "overflow\n");
//        }
//
//        if ((it + 1) % 1 == 0) {
//            double t = now_seconds();
//            printf("iter %d done, elapsed %.6f s\n", it + 1, t - t0);
//        }
//    }
//
//    double t1 = now_seconds();
//    double total = t1 - t0;
//    printf("Total time: %.6f s, avg per iter: %.6f s\n", total, total / ITERS);
//
//    /* print a small checksum so outputs vary with input */
//    double checksum = 0.0;
//    for (size_t i = 0; i < (size_t)B * S * D; i += (D > 0 ? D : 1))
//        checksum += out[i];
//    printf("checksum: %.9f\n", checksum);
//
//    free(Q);
//    free(K);
//    free(V);
//    free(scores);
//    free(out);
//    return 0;
}
