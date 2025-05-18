#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

void printHelp() {
    printf("Usage: print [option] {text}\n");
    printf("Flags:\n");
    printf("  -u {text} : Print in UPPERCASE\n");
    printf("  -l {text} : Print in lowercase\n");
    printf("  -h        : Show this help message\n");
}

void toUpper(char *s) {
    for (int i = 0; s[i]; i++) s[i] = toupper(s[i]);
}

void toLower(char *s) {
    for (int i = 0; s[i]; i++) s[i] = tolower(s[i]);
}

int main(int argc, char *argv[]) {
    int opt;
    int upper = 0, lower = 0;
    opterr = 0;

    while ((opt = getopt(argc, argv, "ulh")) != -1) {
        switch (opt) {
            case 'u':
                upper = 1;
                break;
            case 'l':
                lower = 1;
                break;
            case 'h':
                printHelp();
                return 0;
            case '?':
                printf("unknown option: -%c\n", optopt);
                break;
        }
    }
// Jika ada argumen setelah opsi, print sesuai argumen
    if (optind < argc) {
        printf("ini diprint: ");
        for (int i = optind; i < argc; i++) {
            char *word = strdup(argv[i]);
            if (upper) toUpper(word);
            else if (lower) toLower(word);
            printf("%s ", word);
            free(word);
        }
        printf("\n");
    } else {
        // Tidak ada argumen -> baca dari stdin sampai EOF
        printf("ini diprint: ");
        char buffer[1024];
        while (fgets(buffer, sizeof(buffer), stdin)) {
            if (upper) toUpper(buffer);
            else if (lower) toLower(buffer);
            printf("%s", buffer);
        }
        // Pastikan ada newline jika perlu
        // printf("\n");
    }
    return 0;
}
