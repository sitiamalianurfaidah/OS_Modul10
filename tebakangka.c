#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <getopt.h>

void show_help() {
    printf("Usage: tebakangka [-h] [-m] [-t] [-v]\n");
    printf("Permainan tebak angka.\n\n");
    printf("Options:\n");
    printf("  -h    Tampilkan bantuan\n");
    printf("  -m    Mode maksimal (angka dari 1 sampai 1000)\n");
    printf("  -t    Mode tebakan terbatas (maksimal 10 tebakan)\n");
    printf("  -v    Verbose mode (petunjuk tambahan)\n");
}

int main(int argc, char *argv[]) {
    int opt, max = 100;
    int limited = 0, verbose = 0;

    while ((opt = getopt(argc, argv, "hmtv")) != -1) {
        switch (opt) {
            case 'h':
                show_help();
                return 0;
            case 'm':
                max = 1000;
                break;
            case 't':
                limited = 1;
                break;
            case 'v':
                verbose = 1;
                break;
            default:
                show_help();
                return 1;
        }
    }

    int guess, number;
    int attempts = 0, max_attempts = 10;

    srand(time(NULL));
    number = rand() % max + 1;

    printf("Tebak angka dari 1 sampai %d!\n", max);

    while (1) {
        if (limited && attempts >= max_attempts) {
            printf("Kesempatan habis! Angkanya adalah %d\n", number);
            break;
        }

        printf("Tebakanmu: ");
        if (scanf("%d", &guess) != 1) {
            printf("Input tidak valid.\n");
            // membersihkan input buffer
            while (getchar() != '\n');
            continue;
        }

        attempts++;

        if (guess < number) {
            printf("Terlalu kecil!\n");
            if (verbose) {
                printf("Coba angka yang lebih besar.\n");
            }
        }
        else if (guess > number) {
            printf("Terlalu besar!\n");
            if (verbose) {
                printf("Coba angka yang lebih kecil.\n");
            }
        }
        else {
            printf("Benar! Angkanya adalah %d\n", number);
            printf("Jumlah tebakan: %d\n", attempts);
            break;
        }
    }

    return 0;
}
