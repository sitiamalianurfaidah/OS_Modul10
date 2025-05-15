#include <stdio.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: print {something}\n");
        return 1;
    }
    printf("ini diprint: ");
    for (int i = 1; i < argc; i++)
        printf("%s ", argv[i]);
    printf("\n");
    return 0;
}
