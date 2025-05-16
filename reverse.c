#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <getopt.h>

void show_help() {
    printf("Usage: reverse [-h] [-u] [-l] [-r] {string}\n");
    printf("Membalik string dengan beberapa opsi konversi.\n\n");
    printf("Options:\n");
    printf("  -h    Tampilkan bantuan\n");
    printf("  -u    Konversi string ke uppercase sebelum dibalik\n");
    printf("  -l    Konversi string ke lowercase sebelum dibalik\n");
    printf("  -r    Tampilkan string asli tanpa dibalik\n");
}

void reverse(char *str, int upper, int lower, int no_reverse) {
    int len = strlen(str);

    if (no_reverse) {
        for (int i = 0; i < len; i++) {
            char c = str[i];
            if (upper) c = toupper(c);
            else if (lower) c = tolower(c);
            putchar(c);
        }
        putchar('\n');
        return;
    }

    for (int i = len - 1; i >= 0; i--) {
        char c = str[i];
        if (upper) c = toupper(c);
        else if (lower) c = tolower(c);
        putchar(c);
    }
    putchar('\n');
}

int main(int argc, char *argv[]) {
    int opt;
    int upper = 0, lower = 0, no_reverse = 0;

    while ((opt = getopt(argc, argv, "hulr")) != -1) {
        switch (opt) {
            case 'h':
                show_help();
                return 0;
            case 'u':
                upper = 1;
                break;
            case 'l':
                lower = 1;
                break;
            case 'r':
                no_reverse = 1;
                break;
            default:
                show_help();
                return 1;
        }
    }

    if (optind >= argc) {
        printf("Error: string tidak ditemukan.\n");
        show_help();
        return 1;
    }

    reverse(argv[optind], upper, lower, no_reverse);
    return 0;
}
