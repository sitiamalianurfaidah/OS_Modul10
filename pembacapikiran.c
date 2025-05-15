#include <stdio.h>

void decrypt(char *str) {
    while (*str) {
        *str = *str - 3;
        str++;
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: pembacapikiran {filename}\n");
        return 1;
    }

    FILE *fp = fopen(argv[1], "r");
    if (!fp) {
        perror("fopen");
        return 1;
    }

    printf("Rahasianya: ");

    char word[100];
    while (fscanf(fp, "%s", word) != EOF) {
        decrypt(word);
        printf("%s ", word);
    }
    printf("\n");
    fclose(fp);
    return 0;
}
