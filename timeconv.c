#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void showHelp() {
    printf("Usage: timeconv -s {seconds} [-f {format}]\n");
    printf("Flags:\n");
    printf("  -s {seconds}  : Time in seconds (integer, required)\n");
    printf("  -f {format}   : Output format: hms (default) or m (minutes total)\n");
    printf("  -h            : Show this help message\n");
}

int main(int argc, char *argv[]) {
    int opt;
    int seconds = -1;
    char *format = "hms";

    while ((opt = getopt(argc, argv, "s:f:h")) != -1) {
        switch(opt) {
            case 's':
                seconds = atoi(optarg);
                if (seconds < 0) {
                    fprintf(stderr, "Seconds must be >= 0\n");
                    return 1;
                }
                break;
            case 'f':
                format = optarg;
                break;
            case 'h':
                showHelp();
                return 0;
            default:
                fprintf(stderr, "Unknown option -%c\n", optopt);
                return 1;
        }
    }

    if (seconds < 0) {
        fprintf(stderr, "Missing required flag -s\n");
        return 1;
    }

    if (strcmp(format, "hms") == 0) {
        int h = seconds / 3600;
        int m = (seconds % 3600) / 60;
        int s = seconds % 60;
        printf("%02d:%02d:%02d\n", h, m, s);
    } else if (strcmp(format, "m") == 0) {
        double total_minutes = seconds / 60.0;
        printf("%.2f\n", total_minutes);
    } else {
        fprintf(stderr, "Invalid format: %s\n", format);
        return 1;
    }

    return 0;
}
