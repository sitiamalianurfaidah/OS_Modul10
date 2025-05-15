#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <string.h>
#include <sys/wait.h>

// prototypes
char *takeInput();
void parseInput(char *input);
void landingPage();

int main() {
    landingPage();
    while (1) {
        char *input = takeInput();
        parseInput(input);
    }
    return 0;
}

void landingPage() {
    puts(
        " _____ _____  ___  ______________ _   _ _         _____ \n"
        "|  _  /  ___| |  \\/  |  _  |  _  \\ | | | |       |  _  |\n"
        "| | | \\ `--.  | .  . | | | | | | | | | | |       | |_| |\n"
        "| | | |`--. \\ | |\\/| | | | | | | | | | | |       \\____ |\n"
        "\\ \\_/ /\\__/ / | |  | \\ \\_/ / |/ /| |_| | |____  .___/ /\n"
        " \\___/\\____/  \\_|  |_/\\___/|___/  \\___/\\_____/  \\____/ \n"
        "\n"
        "Siti Amalia Nurfaidah - 2306161851\n"
        "Type \"help\" to see the list of commands\n"
        "Type \"exit\" to quit the shell\n"
    );
}

char *takeInput() {
    char *input;
    while (1) {
        input = readline("netlab>> ");
        if (strlen(input) != 0)
            return input;
    }
}

void parseInput(char *input) {
    if (strcmp(input, "exit") == 0) exit(0);

    add_history(input);

    char *args[100];
    int i = 0;
    char *token = strtok(input, " ");
    while (token != NULL && i < 100) {
        args[i++] = token;
        token = strtok(NULL, " ");
    }
    args[i] = NULL;

    if (args[0] == NULL) return;

    pid_t pid = fork();
    if (pid == 0) {
        // panggil eksekusi command
        if (strcmp(args[0], "help") == 0)
            execv("./printHelp", args);
        else if (strcmp(args[0], "print") == 0)
            execv("./print", args);
        else if (strcmp(args[0], "buatdong") == 0)
            execv("./buatdong", args);
        else if (strcmp(args[0], "bacadong") == 0)
            execv("./bacadong", args);
        else if (strcmp(args[0], "rahasiabanget") == 0)
            execv("./rahasiabanget", args);
        else if (strcmp(args[0], "pembacapikiran") == 0)
            execv("./pembacapikiran", args);
        else if (strcmp(args[0], "itungwoi") == 0)
            execv("./itungwoi", args);

        // === FITUR TAMBAHAN ===
        else if (strcmp(args[0], "warnaku") == 0)
            execv("./warnaku", args);
        else if (strcmp(args[0], "cd") == 0)
            execv("./cdexec", args);
        else if (strcmp(args[0], "listdir") == 0)
            execv("./listdir", args);
        else if (strcmp(args[0], "reverse") == 0)
            execv("./reverse", args);
        else if (strcmp(args[0], "tebakangka") == 0)
            execv("./tebakangka", args);
        else if (strcmp(args[0], "trash") == 0)
            execv("./trash", args);
        else if (strcmp(args[0], "netlab-fortune") == 0)
            execv("./netlab-fortune", args);
        
        else {
            printf("Unknown command: %s\n", args[0]);
            exit(1);
        }
    } else {
        wait(NULL);
    }
}
