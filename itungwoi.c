#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void showHelp() {
    printf("Usage: itungwoi -o {add|sub|mul|div} -a {num1} -b {num2}\n");
    printf("Flags:\n");
    printf("  -o {operation} : Operation to perform (add, sub, mul, div)\n");
    printf("  -a {num1}      : First number\n");
    printf("  -b {num2}      : Second number\n");
    printf("  -h             : Show help\n");
}

int main(int argc, char *argv[]) {
    char *op = NULL;
    float num1 = 0, num2 = 0;
    int opt;
    int got_a = 0, got_b = 0;

    while ((opt = getopt(argc, argv, "o:a:b:h")) != -1) {
        switch (opt) {
            case 'o':
                op = optarg;
                break;
            case 'a':
                num1 = atof(optarg);
                got_a = 1;
                break;
            case 'b':
                num2 = atof(optarg);
                got_b = 1;
                break;
            case 'h':
                showHelp();
                return 0;
            default:
                fprintf(stderr, "Unknown option -%c\n", optopt);
                return 1;
        }
    }

    if (!op || !got_a || !got_b) {
        fprintf(stderr, "Missing required arguments. Use -h for help.\n");
        return 1;
    }

    float result = 0;

    if (strcmp(op, "add") == 0)
        result = num1 + num2;
    else if (strcmp(op, "sub") == 0)
        result = num1 - num2;
    else if (strcmp(op, "mul") == 0)
        result = num1 * num2;
    else if (strcmp(op, "div") == 0) {
        if (num2 == 0) {
            printf("Error: Division by zero!\n");
            return 1;
        }
        result = num1 / num2;
    } else {
        printf("Unknown operation: %s\n", op);
        return 1;
    }

    printf("Result: %.2f\n", result);
    return 0;
}
