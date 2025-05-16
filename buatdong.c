#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void showHelp() {
    printf("Usage: buatdong -f {filename} -c {content}\n");
    printf("Flags:\n");
    printf("  -f {filename} : Name of file to create\n");
    printf("  -c {content}  : Content to write (use quotes for multi-word)\n");
    printf("  -h            : Show this help message\n");
}

int main(int argc, char *argv[]) {
    int opt;
    char *filename = NULL;
    char *content = NULL;

    while ((opt = getopt(argc, argv, "f:c:h")) != -1) {
        switch (opt) {
            case 'f':
                filename = optarg;
                break;
            case 'c':
                content = optarg;
                break;
            case 'h':
                showHelp();
                return 0;
            default:
                fprintf(stderr, "Unknown option -%c\n", optopt);
                return 1;
        }
    }

    if (!filename || !content) {
        fprintf(stderr, "Missing -f or -c flag\n");
        return 1;
    }

    FILE *fp = fopen(filename, "w");
    if (!fp) {
        perror("fopen");
        return 1;
    }
    fprintf(fp, "%s\n", content);
    fclose(fp);
    printf("File %s created and written.\n", filename);
    return 0;
}
