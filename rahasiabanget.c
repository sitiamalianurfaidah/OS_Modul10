#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void encrypt(char *str) {
    while (*str) {
        *str = *str + 3;
        str++;
    }
}

void showHelp() {
    printf("Usage: rahasiabanget -f {filename} -c {content}\n");
    printf("Flags:\n");
    printf("  -f {filename} : Output file name\n");
    printf("  -c {content}  : Content to encrypt (use quotes for multi-word)\n");
    printf("  -h            : Show help message\n");
}

int main(int argc, char *argv[]) {
    char *filename = NULL;
    char *content = NULL;
    int opt;
    int content_start = -1;

    while ((opt = getopt(argc, argv, "f:c:h")) != -1) {
        switch (opt) {
            case 'f':
                filename = optarg;
                break;
            case 'c':
                content_start = optind - 1;
                break;
            case 'h':
                showHelp();
                return 0;
            default:
                fprintf(stderr, "Unknown option -%c\n", optopt);
                return 1;
        }
    }

    if (!filename || content_start == -1) {
        fprintf(stderr, "Missing required arguments. Use -h for help.\n");
        return 1;
    }

    // Hitung panjang total content
    int len = 0;
    for (int i = content_start; i < argc; i++) {
        if (argv[i][0] == '-' && strlen(argv[i]) == 2) break;
        len += strlen(argv[i]) + 1;
    }

    content = malloc(len);
    if (!content) {
        perror("malloc");
        return 1;
    }

    content[0] = '\0';
    for (int i = content_start; i < argc; i++) {
        if (argv[i][0] == '-' && strlen(argv[i]) == 2) break;
        strcat(content, argv[i]);
        if (i < argc - 1) strcat(content, " ");
    }

    encrypt(content);

    FILE *fp = fopen(filename, "w");
    if (!fp) {
        perror("fopen");
        free(content);
        return 1;
    }

    fprintf(fp, "%s\n", content);
    fclose(fp);
    printf("Encrypted file '%s' created.\n", filename);
    free(content);
    return 0;
}
