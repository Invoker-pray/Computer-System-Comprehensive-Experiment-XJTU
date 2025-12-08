#include "logic.h"
#include "transformer_QKV_defines.h"
#include <stdlib.h>
#include <string.h>
int main(int argc, char **argv) {

    if (argument_wrong(argc, argv)) {
        printf("argument wrong.");
        return 0;
    }

    int batch = atoi(argv[1]);
    int sequence_length = atoi(argv[2]);
    int dimention = atoi(argv[3]);
    int iteration = atoi(argv[4]);

    if (batch <= 0 || sequence_length <= 0 || dimention <= 0 ||
        iteration <= 0) {
        fprintf(stderr, "all arguments must be positive integers.\n");
        return 0;
    }

    run_workload(batch, sequence_length, dimention, iteration);
    return 0;
}
