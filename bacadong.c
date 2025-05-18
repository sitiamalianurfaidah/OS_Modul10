#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void printHelp() {
    printf("Usage: bacadong -f {filename} [-n]\n");
    printf("Flags:\n");
    printf("  -f {filename} : File to read\n");
    printf("  -n            : Show line numbers\n");
    printf("  -h            : Show this help message\n");
}


int main(int argc, char *argv[]) {
    char *filename = NULL;
    int showLineNumber = 0;
    int opt;

    while ((opt = getopt(argc, argv, "f:nh")) != -1) {
        switch (opt) {
            case 'f':
                filename = optarg;
                break;
            case 'n':
                showLineNumber = 1;
                break;
            case 'h':
                printHelp();
                return 0;
            default:
                fprintf(stderr, "Unknown option -%c\n", optopt);
                return 1;
        }
    }

    if (!filename) {
        fprintf(stderr, "Filename required. Use -f {filename}\n");
        return 1;
    }

    FILE *fp = fopen(filename, "r");
    if (!fp) {
        perror("fopen");
        return 1;
    }

    char line[1024];
    int lineNum = 1;
    while (fgets(line, sizeof(line), fp)) {
        if (showLineNumber)
            printf("%2d: %s", lineNum++, line);
        else
            printf("%s", line);
    }
    fclose(fp);
    return 0;
}
