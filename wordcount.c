#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

void showHelp() {
    printf("Usage: wordcount [-w] [-l] [-c] [-h] [filename]\n");
    printf("Flags:\n");
    printf("  -w : Count words\n");
    printf("  -l : Count lines\n");
    printf("  -c : Count characters\n");
    printf("  -h : Show this help message\n");
    printf("If no file specified, reads from stdin\n");
}

int main(int argc, char *argv[]) {
    int opt;
    int countWords = 0, countLines = 0, countChars = 0;
    int doWords = 0, doLines = 0, doChars = 0;

    // If no flags given, count all by default
    doWords = doLines = doChars = 0;

    while ((opt = getopt(argc, argv, "wlch")) != -1) {
        switch(opt) {
            case 'w': doWords = 1; break;
            case 'l': doLines = 1; break;
            case 'c': doChars = 1; break;
            case 'h':
                showHelp();
                return 0;
            default:
                fprintf(stderr, "Unknown option -%c\n", optopt);
                return 1;
        }
    }

    // If no -w, -l, -c flags given, count all by default
    if (!doWords && !doLines && !doChars) {
        doWords = doLines = doChars = 1;
    }

    FILE *fp = stdin;
    if (optind < argc) {
        fp = fopen(argv[optind], "r");
        if (!fp) {
            perror("fopen");
            return 1;
        }
    }

    int inWord = 0;
    int c;
    while ((c = fgetc(fp)) != EOF) {
        if (doChars) countChars++;

        if (c == '\n') {
            if (doLines) countLines++;
        }

        if (isspace(c)) {
            inWord = 0;
        } else {
            if (!inWord && doWords) {
                countWords++;
            }
            inWord = 1;
        }
    }

    if (fp != stdin) fclose(fp);

    if (doLines) printf("Lines: %d\n", countLines);
    if (doWords) printf("Words: %d\n", countWords);
    if (doChars) printf("Characters: %d\n", countChars);

    return 0;
}
