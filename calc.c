#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void showHelp() {
    printf("Usage: calc -o {operator} -x {number1} -y {number2}\n");
    printf("Flags:\n");
    printf("  -o {operator} : Operator (+, -, *, /)\n");
    printf("  -x {number1}  : First number (integer or float)\n");
    printf("  -y {number2}  : Second number (integer or float)\n");
    printf("  -h            : Show this help message\n");
}

int main(int argc, char *argv[]) {
    int opt;
    char operator=0;
    double x=0, y=0;
    int x_flag=0, y_flag=0, o_flag=0;

    while ((opt = getopt(argc, argv, "o:x:y:h")) != -1) {
        switch (opt) {
            case 'o':
                operator = optarg[0];
                o_flag = 1;
                break;
            case 'x':
                x = atof(optarg);
                x_flag = 1;
                break;
            case 'y':
                y = atof(optarg);
                y_flag = 1;
                break;
            case 'h':
                showHelp();
                return 0;
            default:
                fprintf(stderr, "Unknown option -%c\n", optopt);
                return 1;
        }
    }

    if (!o_flag || !x_flag || !y_flag) {
        fprintf(stderr, "Missing required flags -o, -x, or -y\n");
        return 1;
    }

    double result=0;
    switch(operator) {
        case '+': result = x + y; break;
        case '-': result = x - y; break;
        case '*': result = x * y; break;
        case '/': 
            if (y == 0) {
                fprintf(stderr, "Error: Division by zero\n");
                return 1;
            }
            result = x / y;
            break;
        default:
            fprintf(stderr, "Invalid operator: %c\n", operator);
            return 1;
    }

    printf("%g\n", result);
    return 0;
}
