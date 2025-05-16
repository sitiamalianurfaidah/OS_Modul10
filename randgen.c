#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

void showHelp() {
    printf("Usage: randgen [-m min] [-M max] [-n count]\n");
    printf("Flags:\n");
    printf("  -m {min}    : Minimum random number (default 0)\n");
    printf("  -M {max}    : Maximum random number (default 100)\n");
    printf("  -n {count}  : Number of random values to generate (default 1)\n");
    printf("  -h          : Show this help message\n");
}

int main(int argc, char *argv[]) {
    int opt;
    int min = 0;
    int max = 100;
    int count = 1;

    while ((opt = getopt(argc, argv, "m:M:n:h")) != -1) {
        switch (opt) {
            case 'm':
                min = atoi(optarg);
                break;
            case 'M':
                max = atoi(optarg);
                break;
            case 'n':
                count = atoi(optarg);
                if (count < 1) {
                    fprintf(stderr, "Count must be >= 1\n");
                    return 1;
                }
                break;
            case 'h':
                showHelp();
                return 0;
            default:
                fprintf(stderr, "Unknown option -%c\n", optopt);
                return 1;
        }
    }

    if (min > max) {
        fprintf(stderr, "Minimum cannot be greater than maximum\n");
        return 1;
    }

    srand(time(NULL));

    for (int i = 0; i < count; i++) {
        int r = (rand() % (max - min + 1)) + min;
        printf("%d\n", r);
    }

    return 0;
}
