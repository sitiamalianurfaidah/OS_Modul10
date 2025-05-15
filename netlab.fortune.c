#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    const char *quotes[] = {
        "Jangan menyerah, karena menyerah itu gampang.",
        "Kopi dulu, koding kemudian.",
        "Semua error pasti ada solusinya, kecuali error di hati.",
        "Keep calm and fork-exec.",
        "Belajar terus walau ngantuk menyerang."
    };

    srand(time(NULL));
    int idx = rand() % (sizeof(quotes) / sizeof(quotes[0]));
    printf(">> %s\n", quotes[idx]);

    return 0;
}
