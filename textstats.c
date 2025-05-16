#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

#define MAX_WORD_LEN 100
#define MAX_WORDS 10000

typedef struct {
    char word[MAX_WORD_LEN];
    int count;
} WordFreq;

void showHelp() {
    printf("Usage: textstats [-f filename] [-c] [-w] [-h]\n");
    printf("Flags:\n");
    printf("  -f filename : Input file (default: stdin)\n");
    printf("  -c          : Show character frequency\n");
    printf("  -w          : Show most frequent words\n");
    printf("  -h          : Show this help message\n");
    printf("If no -c or -w given, shows both\n");
}

int compareFreq(const void *a, const void *b) {
    WordFreq *wa = (WordFreq*)a;
    WordFreq *wb = (WordFreq*)b;
    return wb->count - wa->count;  // descending order
}

int main(int argc, char *argv[]) {
    int opt;
    char *filename = NULL;
    int showCharFreq = 0;
    int showWordFreq = 0;

    while ((opt = getopt(argc, argv, "f:cwh")) != -1) {
        switch(opt) {
            case 'f': filename = optarg; break;
            case 'c': showCharFreq = 1; break;
            case 'w': showWordFreq = 1; break;
            case 'h':
                showHelp();
                return 0;
            default:
                fprintf(stderr, "Unknown option -%c\n", optopt);
                return 1;
        }
    }

    if (!showCharFreq && !showWordFreq) {
        showCharFreq = 1;
        showWordFreq = 1;
    }

    FILE *fp = stdin;
    if (filename) {
        fp = fopen(filename, "r");
        if (!fp) {
            perror("fopen");
            return 1;
        }
    }

    // For char freq: count for all ASCII 0-127
    int charCount[128] = {0};
    // For word freq: store words and their counts
    WordFreq wordFreqs[MAX_WORDS];
    int wordCount = 0;

    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), fp)) {
        // Count char frequency
        if (showCharFreq) {
            for (int i = 0; buffer[i] != '\0'; i++) {
                unsigned char ch = buffer[i];
                if (ch < 128 && !isspace(ch)) {
                    charCount[ch]++;
                }
            }
        }

        // Count word frequency
        if (showWordFreq) {
            // Tokenize words by whitespace and punctuation
            char *p = buffer;
            while (*p) {
                // Skip non-alpha
                while (*p && !isalpha((unsigned char)*p)) p++;
                if (!*p) break;

                char word[MAX_WORD_LEN];
                int i = 0;
                while (*p && isalpha((unsigned char)*p) && i < MAX_WORD_LEN-1) {
                    word[i++] = tolower((unsigned char)*p);
                    p++;
                }
                word[i] = '\0';

                // Check if word already in list
                int found = 0;
                for (int j = 0; j < wordCount; j++) {
                    if (strcmp(wordFreqs[j].word, word) == 0) {
                        wordFreqs[j].count++;
                        found = 1;
                        break;
                    }
                }
                if (!found && wordCount < MAX_WORDS) {
                    strcpy(wordFreqs[wordCount].word, word);
                    wordFreqs[wordCount].count = 1;
                    wordCount++;
                }
            }
        }
    }

    if (fp != stdin) fclose(fp);

    if (showCharFreq) {
        printf("Character frequencies (non-whitespace ASCII):\n");
        for (int i = 32; i < 127; i++) {
            if (charCount[i] > 0) {
                printf(" '%c' : %d\n", i, charCount[i]);
            }
        }
        printf("\n");
    }

    if (showWordFreq) {
        qsort(wordFreqs, wordCount, sizeof(WordFreq), compareFreq);

        printf("Top 10 most frequent words:\n");
        int limit = wordCount < 10 ? wordCount : 10;
        for (int i = 0; i < limit; i++) {
            printf(" %s : %d\n", wordFreqs[i].word, wordFreqs[i].count);
        }
    }

    return 0;
}
