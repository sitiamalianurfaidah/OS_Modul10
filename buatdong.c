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
    int c_index = -1;

    while ((opt = getopt(argc, argv, "f:c:h")) != -1) {
        switch (opt) {
            case 'f':
                filename = optarg;
                break;
            case 'c':
                c_index = optind - 1;
                break;
            case 'h':
                showHelp();
                return 0;
            default:
                fprintf(stderr, "Unknown option -%c\n", optopt);
                return 1;
        }
    }

    if (!filename || c_index == -1) {
        fprintf(stderr, "Missing -f or -c flag\n");
        return 1;
    }

    // Hitung panjang semua argumen setelah -c
    int len = 0;
    for (int i = c_index; i < argc; i++) {
        len += strlen(argv[i]) + 1;
    }

    char *content = malloc(len);
    if (!content) {
        perror("malloc");
        return 1;
    }

    content[0] = '\0';
    for (int i = c_index; i < argc; i++) {
        strcat(content, argv[i]);
        if (i < argc - 1)
            strcat(content, " ");
    }

    FILE *fp = fopen(filename, "w");
    if (!fp) {
        perror("fopen");
        free(content);
        return 1;
    }

    fprintf(fp, "%s\n", content);
    fclose(fp);

    printf("File %s created and written.\n", filename);
    free(content);
    return 0;
}
