#include <stdio.h>

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Usage: buatdong {filename} {content}\n");
        return 1;
    }
    FILE *fp = fopen(argv[1], "w");
    if (!fp) {
        perror("fopen");
        return 1;
    }
    for (int i = 2; i < argc; i++) {
        fprintf(fp, "%s ", argv[i]);
    }
    fclose(fp);
    printf("File %s created and written.\n", argv[1]);
    return 0;
}
