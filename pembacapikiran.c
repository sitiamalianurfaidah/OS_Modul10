#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void decrypt(char *str) {
    while (*str) {
        *str = *str - 3;
        str++;
    }
}

void showHelp() {
    printf("Usage: pembacapikiran -f {filename} [-v]\n");
    printf("Flags:\n");
    printf("  -f {filename} : Encrypted file to read\n");
    printf("  -v            : Verbose mode\n");
    printf("  -h            : Show this help message\n");
}

int main(int argc, char *argv[]) {
    char *filename = NULL;
    int verbose = 0;
    int opt;

    while ((opt = getopt(argc, argv, "f:vh")) != -1) {
        switch (opt) {
            case 'f':
                filename = optarg;
                break;
            case 'v':
                verbose = 1;
                break;
            case 'h':
                showHelp();
                return 0;
            default:
                fprintf(stderr, "Unknown option -%c\n", optopt);
                return 1;
        }
    }

    if (!filename) {
        fprintf(stderr, "Filename is required. Use -f {filename}\n");
        return 1;
    }

    FILE *fp = fopen(filename, "r");
    if (!fp) {
        perror("fopen");
        return 1;
    }

    char word[100];
    if (verbose)
        printf("Reading and decrypting from: %s\n", filename);
    printf("Rahasianya: ");

    while (fscanf(fp, "%s", word) != EOF) {
        decrypt(word);
        printf("%s ", word);
    }
    printf("\n");
    fclose(fp);
    return 0;
}
