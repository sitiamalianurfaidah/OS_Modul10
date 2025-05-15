#include <stdio.h>
#include <string.h>

void reverse(char *str) {
    int len = strlen(str);
    for (int i = len - 1; i >= 0; i--)
        putchar(str[i]);
    putchar('\n');
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: reverse {string}\n");
        return 1;
    }

    reverse(argv[1]);
    return 0;
}
