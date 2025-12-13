#include<stdio.h>
#include<math.h>
#include<string.h>
#include "../defines.h" 
#include "../qkv_clstr_hw_defines.h"
#define HEADS 4
#define D_HEAD (64/HEADS)
#define IDX(i,j,ld) ((i)*(j)+(ld))
void qkv(){
	TYPE *q = (TYPE *)query;	
	TYPE *k = (TYPE *)key;
	TYPE *v = (TYPE *)value;
	TYPE *o = (TYPE *)output;

	static TYPE score[ROW][COL];
	static TYPE attention[ROW][COL];
	static TYPE out_head[ROW][D_HEAD];

	const TYPE scale=1.0/sqrt((TYPE)D_HEAD);

	memset(o, 0, sizeof(TYPE) * 64 * 64);

	for(int h = 0; h < HEADS; h++){
	int offset = h * D_HEAD;
	
	// Q * K^T
	for(int i = 0; i < 64; i++){
		for(int j = 0; j < 64; j++){
			TYPE sum = 0.0;
			for(int d = 0; d < D_HEAD; d++){
				sum += q[IDX(i, 64, offset + d)] * k[IDX(j, 64, offset + d)]; 
			}
			score[i][j] = sum * scale;
		}
	}



	//softmax
	for(int i = 0; i < 64; i++){
		TYPE max_val = score[i][0];
		for(int j = 1; j < 64; j++){
			if(score[i][j] > max_val){
				max_val = score[i][j];
			}
		}

		TYPE sum_exp = 0.0;
		
		for (int j = 0; j < 64; j++){
		attention[i][j] = exp(score[i][j] - max_val);
		sum_exp += attention[i][j];
		}

		for(int j = 0; j < 64; j++){
			attention[i][j] /=sum_exp;
		}

	}

	// Attention  dot  value
	for(int i = 0; i < 64; i++){
		for(int d = 0; d < D_HEAD; d++){
			TYPE sum = 0.0;
			for(int j = 0; j < 64; j++){
				sum += attention[i][j] * v[IDX(j, 64, offset + d)];
			}
			out_head[i][d] = sum;
		}
	}

	// concat
	
	for(int i = 0; i < 64; i++){
		for(int d = 0; d < D_HEAD; d++){
			o[IDX(i, 64, offset+d)] = out_head[i][d];
		}
	}

	
	




	

	}



}
