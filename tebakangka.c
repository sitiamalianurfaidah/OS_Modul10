#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int guess, number;
    srand(time(NULL));
    number = rand() % 100 + 1;

    printf("Tebak angka dari 1 sampai 100!\n");

    while (1) {
        printf("Tebakanmu: ");
        scanf("%d", &guess);

        if (guess < number) {
            printf("Terlalu kecil!\n");
        } else if (guess > number) {
            printf("Terlalu besar!\n");
        } else {
            printf("Benar! Angkanya adalah %d\n", number);
            break;
        }
    }

    return 0;
}
