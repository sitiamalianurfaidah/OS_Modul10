#include <stdio.h>
#include <dirent.h>
#include <unistd.h>
#include <getopt.h>
#include <string.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

void show_help() {
    printf("Usage: listdir [-h] [-a] [-l] [-r]\n");
    printf("Menampilkan isi direktori saat ini.\n\n");
    printf("Options:\n");
    printf("  -h    Tampilkan bantuan\n");
    printf("  -a    Tampilkan semua file termasuk yang tersembunyi\n");
    printf("  -l    Tampilkan detail file\n");
    printf("  -r    Tampilkan daftar file secara terbalik\n");
}

void print_file_info(const char *name) {
    struct stat st;
    if (stat(name, &st) == -1) {
        perror("stat");
        return;
    }

    // Permissions
    printf( (S_ISDIR(st.st_mode)) ? "d" : "-");
    printf( (st.st_mode & S_IRUSR) ? "r" : "-");
    printf( (st.st_mode & S_IWUSR) ? "w" : "-");
    printf( (st.st_mode & S_IXUSR) ? "x" : "-");
    printf( (st.st_mode & S_IRGRP) ? "r" : "-");
    printf( (st.st_mode & S_IWGRP) ? "w" : "-");
    printf( (st.st_mode & S_IXGRP) ? "x" : "-");
    printf( (st.st_mode & S_IROTH) ? "r" : "-");
    printf( (st.st_mode & S_IWOTH) ? "w" : "-");
    printf( (st.st_mode & S_IXOTH) ? "x" : "-");

    // User and group
    struct passwd *pw = getpwuid(st.st_uid);
    struct group  *gr = getgrgid(st.st_gid);
    printf(" %s %s", pw ? pw->pw_name : "?", gr ? gr->gr_name : "?");

    // Size
    printf(" %5ld", st.st_size);

    // Modification time
    char timebuf[80];
    struct tm *tm_info = localtime(&st.st_mtime);
    strftime(timebuf, sizeof(timebuf), "%b %d %H:%M", tm_info);
    printf(" %s", timebuf);

    printf(" %s\n", name);
}

int main(int argc, char *argv[]) {
    int opt, showAll = 0, detailed = 0, reverse = 0;
    while ((opt = getopt(argc, argv, "halr")) != -1) {
        switch (opt) {
            case 'h':
                show_help();
                return 0;
            case 'a':
                showAll = 1;
                break;
            case 'l':
                detailed = 1;
                break;
            case 'r':
                reverse = 1;
                break;
            default:
                show_help();
                return 1;
        }
    }

    DIR *d = opendir(".");
    if (!d) {
        perror("opendir");
        return 1;
    }

    struct dirent *dir;
    // Simpan nama file dulu karena kita mungkin reverse output
    #define MAX_FILES 1024
    char *files[MAX_FILES];
    int count = 0;

    while ((dir = readdir(d)) != NULL) {
        if (!showAll && dir->d_name[0] == '.') continue;
        if (count < MAX_FILES) {
            files[count] = strdup(dir->d_name);
            count++;
        }
    }
    closedir(d);

    if (reverse) {
        for (int i = count - 1; i >= 0; i--) {
            if (detailed)
                print_file_info(files[i]);
            else
                printf("%s\n", files[i]);
            free(files[i]);
        }
    } else {
        for (int i = 0; i < count; i++) {
            if (detailed)
                print_file_info(files[i]);
            else
                printf("%s\n", files[i]);
            free(files[i]);
        }
    }

    return 0;
}
