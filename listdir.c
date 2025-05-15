#include <stdio.h>
#include <dirent.h>

int main() {
    DIR *d;
    struct dirent *dir;
    d = opendir(".");

    if (!d) {
        perror("opendir");
        return 1;
    }

    printf("Files in current directory:\n");
    while ((dir = readdir(d)) != NULL) {
        printf("%s\n", dir->d_name);
    }

    closedir(d);
    return 0;
}
