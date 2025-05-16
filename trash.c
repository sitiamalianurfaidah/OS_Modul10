#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <getopt.h>

void show_help() {
    printf("Usage: trash [-h] [-d folder] [-f] [-v] {filename}\n");
    printf("Memindahkan file ke folder trash (default: ./.trash)\n\n");
    printf("Options:\n");
    printf("  -h          Tampilkan bantuan\n");
    printf("  -d folder   Gunakan folder trash kustom\n");
    printf("  -f          Force overwrite jika file sudah ada di trash\n");
    printf("  -v          Tampilkan proses secara detail (verbose)\n");
}

int main(int argc, char *argv[]) {
    int opt;
    char trashPath[256] = "./.trash";
    int force = 0;
    int verbose = 0;

    while ((opt = getopt(argc, argv, "hd:fv")) != -1) {
        switch (opt) {
            case 'h':
                show_help();
                return 0;
            case 'd':
                strncpy(trashPath, optarg, sizeof(trashPath) - 1);
                trashPath[sizeof(trashPath)-1] = '\0';
                break;
            case 'f':
                force = 1;
                break;
            case 'v':
                verbose = 1;
                break;
            default:
                show_help();
                return 1;
        }
    }

    if (optind >= argc) {
        printf("Error: file tidak ditentukan.\n");
        show_help();
        return 1;
    }

    char *filename = argv[optind];
    char destPath[512];

    if (verbose) printf("Membuat folder trash jika belum ada: %s\n", trashPath);
    mkdir(trashPath, 0755);

    snprintf(destPath, sizeof(destPath), "%s/%s", trashPath, filename);

    // Cek apakah file tujuan sudah ada
    if (access(destPath, F_OK) == 0) {
        if (!force) {
            printf("File '%s' sudah ada di trash. Gunakan -f untuk overwrite.\n", filename);
            return 1;
        } else if (verbose) {
            printf("File '%s' sudah ada di trash, akan ditimpa karena mode force aktif.\n", filename);
        }
    }

    if (verbose) printf("Memindahkan file '%s' ke '%s'...\n", filename, destPath);

    if (rename(filename, destPath) != 0) {
        perror("Gagal memindahkan file ke trash");
        return 1;
    }

    printf("File berhasil dipindahkan ke %s\n", trashPath);
    return 0;
}
