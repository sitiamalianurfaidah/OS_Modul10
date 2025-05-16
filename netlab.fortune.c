#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <getopt.h>
#include <string.h>

#define MAX_QUOTES 100
#define MAX_QUOTE_LEN 256

void show_help() {
    printf("Usage: netlab.fortune [-h] [-n jumlah] [-r] [-f file]\n");
    printf("Menampilkan quote random ala netlab.\n\n");
    printf("Options:\n");
    printf("  -h         Tampilkan bantuan\n");
    printf("  -n jumlah  Tampilkan beberapa quote sekaligus\n");
    printf("  -r         Izinkan quote berulang (default: tidak)\n");
    printf("  -f file    Baca quotes dari file eksternal\n");
}

// Fungsi baca quotes dari file
int load_quotes(const char *filename, char quotes[][MAX_QUOTE_LEN]) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        perror("Gagal membuka file quotes");
        return -1;
    }
    int count = 0;
    while (count < MAX_QUOTES && fgets(quotes[count], MAX_QUOTE_LEN, fp)) {
        size_t len = strlen(quotes[count]);
        if (len > 0 && quotes[count][len-1] == '\n')
            quotes[count][len-1] = '\0';  // hapus newline
        count++;
    }
    fclose(fp);
    return count;
}

int main(int argc, char *argv[]) {
    const char *default_quotes[] = {
        "Jangan menyerah, karena menyerah itu gampang.",
        "Kopi dulu, koding kemudian.",
        "Semua error pasti ada solusinya, kecuali error di hati.",
        "Keep calm and fork-exec.",
        "Belajar terus walau ngantuk menyerang."
    };
    int count = 1;
    int allow_repeat = 0;  // default tidak mengizinkan pengulangan
    char quotes[MAX_QUOTES][MAX_QUOTE_LEN];
    int totalQuotes = sizeof(default_quotes) / sizeof(default_quotes[0]);
    int opt;
    char *filename = NULL;

    while ((opt = getopt(argc, argv, "hn:rf:")) != -1) {
        switch (opt) {
            case 'h':
                show_help();
                return 0;
            case 'n':
                count = atoi(optarg);
                if (count <= 0) count = 1;
                break;
            case 'r':
                allow_repeat = 1;
                break;
            case 'f':
                filename = optarg;
                break;
            default:
                show_help();
                return 1;
        }
    }

    // Load quotes from file jika ada, jika gagal tetap pakai default
    if (filename) {
        int loaded = load_quotes(filename, quotes);
        if (loaded > 0) {
            totalQuotes = loaded;
        } else {
            fprintf(stderr, "Menggunakan quotes default karena gagal baca file.\n");
            // Copy default quotes ke array quotes
            for (int i = 0; i < totalQuotes; i++) {
                strncpy(quotes[i], default_quotes[i], MAX_QUOTE_LEN);
            }
        }
    } else {
        // Copy default quotes ke array quotes
        for (int i = 0; i < totalQuotes; i++) {
            strncpy(quotes[i], default_quotes[i], MAX_QUOTE_LEN);
        }
    }

    srand(time(NULL));
    int *used = NULL;
    if (!allow_repeat && count > totalQuotes) {
        count = totalQuotes;  // batasi supaya tidak lebih dari jumlah quote
    }

    if (!allow_repeat) {
        used = calloc(totalQuotes, sizeof(int));
    }

    for (int i = 0; i < count; i++) {
        int idx;
        if (allow_repeat) {
            idx = rand() % totalQuotes;
        } else {
            // Cari quote yang belum dipakai
            do {
                idx = rand() % totalQuotes;
            } while (used[idx]);
            used[idx] = 1;
        }
        printf(">> %s\n", quotes[idx]);
    }

    free(used);
    return 0;
}
