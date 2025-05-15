#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: trash {filename}\n");
        return 1;
    }

    char trashPath[256] = "./.trash";
    char destPath[512];

    // buat folder trash kalau belum ada
    mkdir(trashPath, 0755);

    snprintf(destPath, sizeof(destPath), "%s/%s", trashPath, argv[1]);

    if (rename(argv[1], destPath) != 0) {
        perror("Gagal memindahkan file ke trash");
        return 1;
    }

    printf("File berhasil dipindahkan ke .trash\n");
    return 0;
}
