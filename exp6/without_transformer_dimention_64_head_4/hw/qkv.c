#include "../defines.h"
#include "../qkv_clstr_hw_defines.h"
#define IDX(i, j, k) ((i) * (j) + (k))
#define HEADS 2
#define D_HEAD (N / HEADS)
#define N 64
void qkv() {
    TYPE *q = (TYPE *)query;
    TYPE *k = (TYPE *)key;
    TYPE *v = (TYPE *)value;
    TYPE *o = (TYPE *)output;

    TYPE *s = (TYPE *)score;
    TYPE *a = (TYPE *)attention;
    TYPE *oh = (TYPE *)out_head;
    const TYPE scale = 0.707;

    for (int h = 0; h < HEADS; h++) {
        int offset = h * D_HEAD;
        // Q*K^T
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                TYPE sum = 0.0;
                for (int d = 0; d < D_HEAD; d++) {
                    sum += q[IDX(i, N, offset + d)] * k[IDX(j, N, offset + d)];
                }
                s[IDX(i, N, j)] = sum * scale;
            }
        }

        // softmax
        for (int i = 0; i < N; i++) {
            TYPE max_val = s[IDX(i, N, 0)];
            for (int j = 1; j < N; j++) {
                if (s[IDX(i, N, j)] > max_val) {
                    max_val = s[IDX(i, N, j)];
                }
            }
            TYPE sum_exp = 0.0;

            for (int j = 0; j < N; j++) {
                double x = s[IDX(i, N, j)] - max_val;
                double term = 1.0;
                double sum = 1.0;

                for (int p = 1; p <= 7; p++) {
                    term *= x / p;
                    sum += term;
                }
                a[IDX(i, N, j)] = sum;
                sum_exp += a[IDX(i, N, j)];
            }

            for (int j = 0; j < N; j++) {
                a[IDX(i, N, j)] /= sum_exp;
            }
        }

        // atention dot value

        for (int i = 0; i < N; i++) {
            for (int d = 0; d < D_HEAD; d++) {
                TYPE sum = 0.0;
                for (int j = 0; j < N; j++) {
                    sum += a[IDX(i, N, j)] * v[IDX(j, N, offset + d)];
                }
                oh[IDX(i, N, d)] = sum;
            }
        }

	// layer norm
	const TYPE eps = 1e-5;

	for(int i = 0; i < N; i++){
		TYPE mean = 0.0;
		for(int d = 0; d < D_HEAD; d++){
			mean += oh[IDX(i, N, d)];
		}
		mean /= D_HEAD;

		TYPE var = 0.0;
		for(int d = 0; d < D_HEAD; d++){
			TYPE diff = oh[IDX(i, N, d)] - mean;
			var += diff * diff;
		}

		var /= D_HEAD;
		TYPE temp1 = var + eps;
		TYPE result1 = temp1 * 0.5f;

		for (int i = 0; i < 5; i++){
			result1 = 0.5f * (result1 + temp1 / result1);
		}

		TYPE inv_std = 1.0 / result1;

		for (int d = 0; d < D_HEAD; d++){
			oh[IDX(i, N, d)] = (oh[IDX(i, N, d)] - mean) * inv_std;
		}



	}

	// relu
	
	for (int i = 0; i < N; i++){
		for (int d = 0; d < D_HEAD; d++){
			TYPE x = oh[IDX(i, N, d)];
			oh[IDX(i, N, d)] = (x > 0) ? x : 0;
		}
	}
        // concat
        for (int i = 0; i < N; i++) {
            for (int d = 0; d < D_HEAD; d++) {
                o[IDX(i, N, offset + d)] = oh[IDX(i, N, d)];
            }
        }
    }
}
