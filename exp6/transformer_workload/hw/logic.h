#include <stdio.h>
bool arugment_wrong(int argc, char **argv) {
    if (argc < 5) {
        fprintf(stderr,
                "Usage: <batch> <sequence_length> <dimentions> <iterations>\n",
                argv[0]);

        fprintf(stderr, "Example: 1 512 1024 10\n", argv[0]);
        return 1;
    } else {
        return 0;
    }
}
