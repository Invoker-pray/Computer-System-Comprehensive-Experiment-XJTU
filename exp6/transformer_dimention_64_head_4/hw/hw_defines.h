// Standard Libraries
#include "../defines.h"
#include "../qkv_clstr_hw_defines.h"
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define DEV_INIT 0x01
#define DEV_INTR 0x04

// Specify row/column sizes
#define row_size ROW
#define col_size COL
#define qkv_size sizeof(TYPE) * row_size * col_size
