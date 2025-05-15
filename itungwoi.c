#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Usage: itungwoi {add|sub|mul|div} num1 num2\n");
        return 1;
    }

    float num1 = atof(argv[2]);
    float num2 = atof(argv[3]);
    float result;

    if (strcmp(argv[1], "add") == 0)
        result = num1 + num2;
    else if (strcmp(argv[1], "sub") == 0)
        result = num1 - num2;
    else if (strcmp(argv[1], "mul") == 0)
        result = num1 * num2;
    else if (strcmp(argv[1], "div") == 0) {
        if (num2 == 0) {
            printf("Error: Division by zero!\n");
            return 1;
        }
        result = num1 / num2;
    } else {
        printf("Unknown operation: %s\n", argv[1]);
        return 1;
    }

    printf("Result: %.2f\n", result);
    return 0;
}
