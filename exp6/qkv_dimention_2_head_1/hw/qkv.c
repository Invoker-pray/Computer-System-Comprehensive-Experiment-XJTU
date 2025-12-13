#include "../defines.h" 
#include "../qkv_clstr_hw_defines.h"
#define IDX(i,j,k) ((i)*(j)+(k))
#define HEADS 1
#define D_HEAD (2/HEADS)
#define N 2
void qkv(){
	TYPE *q = (TYPE *)query;	
	TYPE *k = (TYPE *)key;
	TYPE *v = (TYPE *)value;
	TYPE *o = (TYPE *)output;

	TYPE *s = (TYPE *) score;
	TYPE *a = (TYPE *) attention;
	TYPE *oh = (TYPE *) out_head;	
	const TYPE scale=0.707;
	

	for(int h = 0 ; h < HEADS; h++){
		int offset = h * D_HEAD;
	//Q*K^T
	for(int i = 0; i < N; i++){
		for(int j = 0; j < N; j++){
			TYPE sum = 0.0;
			for(int d = 0; d < D_HEAD; d++){
			sum += q[IDX(i,N,offset+d)] * k[IDX(j,N,offset+d)];
			}
			s[IDX(i, N, j)] = sum * scale;
		}
	}


	//softmax
	for(int i =0 ; i < N; i++){
		TYPE max_val = s[IDX(i, N, 0)];
		for(int j = 1; j < N; j++){
			if(s[IDX(i, N, j)] > max_val){
				max_val = s[IDX(i,N,j)];
			}
		}
		TYPE sum_exp = 0.0;

		for(int j = 0; j < N; j++){
			double x = s[IDX(i, N, j)] - max_val;
			double term = 1.0;
			double sum = 1.0;

			for(int p = 1; p <= 7; p++){
				term *=x/p;
				sum += term;
			} 
			a[IDX(i, N, j)]=sum;
			sum_exp += a[IDX(i,N,j)];
		}

		for (int j = 0; j < N; j++ ){
			a[IDX(i, N, j)] /= sum_exp;
		}

	}


	// atention dot value
	
	for(int i = 0; i < N; i++){
		for(int d = 0; d < D_HEAD; d++){
			TYPE sum = 0.0;
			for(int j = 0; j < N; j++){
				sum +=a[IDX(i, N, j)] * v[IDX(j, N, offset+d)];
			}
			oh[IDX(i, N, d)] = sum;
		}
	}

	// concat
	for (int i = 0;i < N; i ++ ){
		for(int d = 0; d < D_HEAD; d++){
			o[IDX(i,N, offset+d)]=oh[IDX(i,N,d)];
		}
	}
}	
}
