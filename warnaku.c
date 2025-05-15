#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Daftar warna teks ANSI
const char *colors[] = {
    "\033[0;31m",  // Merah
    "\033[0;32m",  // Hijau
    "\033[0;33m",  // Kuning
    "\033[0;34m",  // Biru
    "\033[0;35m",  // Ungu
    "\033[0;36m",  // Cyan
    "\033[0;37m",  // Putih
    "\033[1;31m",  // Merah terang
    "\033[1;32m",  // Hijau terang
    "\033[1;33m",  // Kuning terang
    "\033[1;34m",  // Biru terang
    "\033[1;35m",  // Ungu terang
    "\033[1;36m",  // Cyan terang
    "\033[1;37m",  // Putih terang
};

// Fungsi untuk memilih warna acak dan menampilkan teks dengan warna tersebut
void changeColor() {
    srand(time(NULL));  // Seed untuk random
    int colorIdx = rand() % (sizeof(colors) / sizeof(colors[0]));  // Pilih indeks warna acak
    printf("%sWarna teks berubah! Selamat mencoba warnaku!\n", colors[colorIdx]);
    printf("\033[0m");  // Reset warna ke default
}

int main() {
    changeColor();  // Panggil fungsi untuk mengganti warna teks
    return 0;
}
