#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <string.h>
#include <sys/wait.h>
#include <signal.h>

#define MAX_ARGS 100
#define MAX_COMMAND_LENGTH 1024

void sigintHandler(int sig);
void landingPage();
char *takeInput();
void parseInput(char *input);
void executeCommand(char *cmd);

int main() {
    signal(SIGINT, sigintHandler);  // handle Ctrl+C

    landingPage();

    while (1) {
        char *input = takeInput();
        if (input == NULL) {
            printf("\n"); // Ctrl+D exit gracefully
            break;
        }
        // skip empty input
        if (strlen(input) > 0) {
            parseInput(input);
        }
        free(input);
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
    char *input = readline("netlab>> ");
    if (input && strlen(input) > 0)
        add_history(input);
    return input;
}

void sigintHandler(int sig) {
    printf("\n(Ctrl+C ignored, use \"exit\" to quit)\n");
    fflush(stdout);
}

void parseInput(char *input) {
    // Trim leading spaces
    while (*input == ' ' || *input == '\t') input++;

    if (strcmp(input, "exit") == 0) exit(0);

    // Check pipe
    char *pipePos = strchr(input, '|');
    if (pipePos != NULL) {
        *pipePos = '\0';
        char *cmd1 = input;
        char *cmd2 = pipePos + 1;

        // Trim trailing spaces in cmd1
        char *end = cmd1 + strlen(cmd1) - 1;
        while (end > cmd1 && (*end == ' ' || *end == '\t')) {
            *end = '\0';
            end--;
        }

        // Trim leading spaces in cmd2
        while (*cmd2 == ' ' || *cmd2 == '\t') cmd2++;

        int fd[2];
        if (pipe(fd) == -1) {
            perror("pipe failed");
            return;
        }

        pid_t pid1 = fork();
        if (pid1 == -1) {
            perror("fork failed");
            return;
        }

        if (pid1 == 0) {
            // child 1: stdout -> pipe write
            close(fd[0]);
            dup2(fd[1], STDOUT_FILENO);
            close(fd[1]);
            executeCommand(cmd1);
            exit(EXIT_FAILURE);
        }

        pid_t pid2 = fork();
        if (pid2 == -1) {
            perror("fork failed");
            return;
        }

        if (pid2 == 0) {
            // child 2: stdin <- pipe read
            close(fd[1]);
            dup2(fd[0], STDIN_FILENO);
            close(fd[0]);
            executeCommand(cmd2);
            exit(EXIT_FAILURE);
        }

        // parent
        close(fd[0]);
        close(fd[1]);
        waitpid(pid1, NULL, 0);
        waitpid(pid2, NULL, 0);

    } else {
        executeCommand(input);
    }
}

void executeCommand(char *cmd) {
    // Tokenize command line
    char *args[MAX_ARGS];
    int i = 0;

    // Duplicate cmd string to avoid strtok modifying original
    char *cmd_copy = strdup(cmd);
    if (!cmd_copy) {
        perror("strdup failed");
        return;
    }

    char *token = strtok(cmd_copy, " \t\n");
    while (token != NULL && i < MAX_ARGS - 1) {
        args[i++] = token;
        token = strtok(NULL, " \t\n");
    }
    args[i] = NULL;

    if (args[0] == NULL) {
        free(cmd_copy);
        return;
    }

    // Handle cd inside shell process (built-in)
    if (strcmp(args[0], "cd") == 0) {
        if (args[1] == NULL) {
            fprintf(stderr, "cd: missing argument\n");
        } else {
            if (chdir(args[1]) != 0) {
                perror("cd failed");
            }
        }
        free(cmd_copy);
        return;
    }

    // Fork to execute external commands
    pid_t pid = fork();
    if (pid < 0) {
        perror("fork failed");
        free(cmd_copy);
        return;
    } else if (pid == 0) {
        // Child process exec commands
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
        else if (strcmp(args[0], "warnaku") == 0)
            execv("./warnaku", args);
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
        else if (strcmp(args[0], "kalkulator") == 0)
            execv("./kalkulator", args);
        else if (strcmp(args[0], "konversiwaktu") == 0)
            execv("./konversiwaktu", args);
        else if (strcmp(args[0], "randomgen") == 0)
            execv("./randomgen", args);
        else if (strcmp(args[0], "wordcount") == 0)
            execv("./wordcount", args);
        else if (strcmp(args[0], "textstats") == 0)
            execv("./textstats", args);
        else {
                printf("Unknown command: %s\n", args[0]);
                exit(EXIT_FAILURE);
            }
        // execv failed
        perror("execv failed");
        exit(EXIT_FAILURE);
    } else {
        // Parent wait child
        int status;
        waitpid(pid, &status, 0);
    }

    free(cmd_copy);
}
