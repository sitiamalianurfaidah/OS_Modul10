#include <stdio.h>
#include <string.h>

void encrypt(char *str) {
    while (*str) {
        *str = *str + 3;
        str++;
    }
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Usage: rahasiabanget {filename} {content}\n");
        return 1;
    }
    FILE *fp = fopen(argv[1], "w");
    if (!fp) {
        perror("fopen");
        return 1;
    }
    for (int i = 2; i < argc; i++) {
        encrypt(argv[i]);
        fprintf(fp, "%s ", argv[i]);
    }
    fclose(fp);
    printf("Encrypted file %s created.\n", argv[1]);
    return 0;
}
