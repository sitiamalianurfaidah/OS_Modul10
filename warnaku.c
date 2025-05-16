#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <getopt.h>

const char *colors[] = {
    "\033[0;31m", "\033[0;32m", "\033[0;33m", "\033[0;34m",
    "\033[0;35m", "\033[0;36m", "\033[0;37m", "\033[1;31m",
    "\033[1;32m", "\033[1;33m", "\033[1;34m", "\033[1;35m",
    "\033[1;36m", "\033[1;37m"
};

void show_help() {
    printf("Usage: warnaku [-h] [-s] [-r] [-c <number>]\n");
    printf("Menampilkan teks dengan warna acak atau warna pilihan.\n\n");
    printf("Options:\n");
    printf("  -h           Tampilkan bantuan\n");
    printf("  -s           Silent mode (hanya warna, tanpa pesan)\n");
    printf("  -r           Reset warna menjadi default (tanpa warna)\n");
    printf("  -c <number>  Pilih warna tertentu berdasarkan indeks warna (0-13)\n");
}

void changeColor(int silent, int reset, int colorIdx) {
    if (reset) {
        printf("\033[0m");
        if (!silent) {
            printf("Warna direset ke default.\n");
        }
        return;
    }

    if (colorIdx >= 0 && colorIdx < (int)(sizeof(colors) / sizeof(colors[0]))) {
        printf("%s", colors[colorIdx]);
    } else {
        // warna acak jika indeks tidak valid
        srand(time(NULL));
        int randIdx = rand() % (sizeof(colors) / sizeof(colors[0]));
        printf("%s", colors[randIdx]);
    }

    if (!silent) {
        printf("Warna teks berubah! Selamat mencoba warnaku!\n");
    }
    printf("\033[0m");
}

int main(int argc, char *argv[]) {
    int opt;
    int silent = 0;
    int reset = 0;
    int colorIdx = -1;

    while ((opt = getopt(argc, argv, "hsrc:")) != -1) {
        switch (opt) {
            case 'h':
                show_help();
                return 0;
            case 's':
                silent = 1;
                break;
            case 'r':
                reset = 1;
                break;
            case 'c':
                colorIdx = atoi(optarg);
                break;
            default:
                show_help();
                return 1;
        }
    }

    changeColor(silent, reset, colorIdx);
    return 0;
}
