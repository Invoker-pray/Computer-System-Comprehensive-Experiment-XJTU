#include "../defines.h"

volatile int stage;



static float frandf(unsigned *seed) {
    *seed = (*seed * 1664525u) + 1013904223u;
    return (float)(*seed & 0xFFFFFF) / (float)0x1000000;
}

void random_generate(TYPE* m1, TYPE* m2, TYPE* m3){
	unsigned seed = 123456789;
	for (int i = 0; i < ROW*COL ; ++i) {
        	m1[i] = frandf(&seed) - 0.5f;
        	m2[i] = frandf(&seed) - 0.5f;
       		m3[i] = frandf(&seed) - 0.5f;
    	}
	
}
	


