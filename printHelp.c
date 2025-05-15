#include <stdio.h>

int main() {
    puts(
        "Siti Amalia Nurfaidah - 2306161851\n"
        "- Use the shell at your own risk...\n"
        "List of Commands supported:\n"
        "\n"
        ">> Basic Commands:\n"
        "> help                        : Show all commands in shell\n"
        "> exit                        : Exit the shell\n"
        "> print {something}           : Print something to the screen\n"
        "\n"
        ">> File Handling:\n"
        "> buatdong {filename} {content}        : Write content to a file\n"
        "> bacadong {filename}                  : Read content from a file\n"
        "> rahasiabanget {filename}            : Write encrypted content to file\n"
        "> pembacapikiran {filename}           : Read encrypted file content\n"
        "\n"
        ">> Calculator:\n"
        "> itungwoi {add|sub|mul|div} num1 num2 : Do a basic calculation\n"
        "\n"
        ">> Additional Features:\n"
        "> warnaku                    : Change text color randomly\n"
        "> listdir                    : List all files and folders in current directory\n"
        "> reverse {text}            : Reverse a string and print it\n"
        "> tebakangka                 : Play a guessing number game\n"
        "> trash {filename}          : Move a file to .trash folder\n"
        "> netlab-fortune            : Get a random wise quote from Netlab\n"
    );
    return 0;
}
