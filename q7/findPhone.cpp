#include <unistd.h>
#include <sys/wait.h>
#include <iostream>
#include <cctype>
using namespace std;

// Validates that a name contains only letters and spaces
bool isValidName(const char* part) {
    for (int i = 0; part[i] != '\0'; ++i) {
        if (!isalpha(part[i]) && part[i] != ' ') {
            return false;
        }
    }
    return true;
}

int main(int argc, char *argv[]) {
    // Check for sufficient arguments
    if (argc < 2) {
        cerr << "Usage: ./findPhone <first name>\n";
        return 1;
    }

    // Build full name from command line arguments
    char name[256];
    int index = 0;
    for (int i = 1; i < argc; ++i) {
        if (!isValidName(argv[i])) {
            cerr << "Error: Name must contain only letters and spaces.\n";
            return 1;
        }
        for (int j = 0; argv[i][j] != '\0'; ++j) {
            if (index >= 255) {
                cerr << "Error: Name too long.\n";
                return 1;
            }
            name[index++] = argv[i][j];
        }
        if (i < argc - 1) name[index++] = ' ';
    }
    name[index] = '\0';

    // Create pipes for inter-process communication
    int pipe1[2], pipe2[2], pipe3[2];
    if (pipe(pipe1) == -1 || pipe(pipe2) == -1 || pipe(pipe3) == -1) {
        perror("pipe failed");
        return 1;
    }

    pid_t pids[4];

    // Process 1: grep <name> phonebook.txt
    pids[0] = fork();
    if (pids[0] < 0) {
        perror("fork grep");
        return 1;
    } else if (pids[0] == 0) {
        dup2(pipe1[1], STDOUT_FILENO);
        close(pipe1[0]); close(pipe1[1]);
        execlp("grep", "grep", name, "phonebook.txt", NULL);
        perror("exec grep");
        exit(1);
    }
    close(pipe1[1]);

    // Process 2: sed 's/ /#/g'
    pids[1] = fork();
    if (pids[1] < 0) {
        perror("fork sed1");
        return 1;
    } else if (pids[1] == 0) {
        dup2(pipe1[0], STDIN_FILENO);
        dup2(pipe2[1], STDOUT_FILENO);
        close(pipe1[0]);
        close(pipe2[0]); close(pipe2[1]);
        execlp("sed", "sed", "s/ /#/g", NULL);
        perror("exec sed1");
        exit(1);
    }
    close(pipe1[0]);

    // Process 3: sed 's/,/ /'
    pids[2] = fork();
    if (pids[2] < 0) {
        perror("fork sed2");
        return 1;
    } else if (pids[2] == 0) {
        dup2(pipe2[0], STDIN_FILENO);
        dup2(pipe3[1], STDOUT_FILENO);
        close(pipe2[0]); close(pipe2[1]);
        close(pipe3[0]); close(pipe3[1]);
        execlp("sed", "sed", "s/,/ /", NULL);
        perror("exec sed2");
        exit(1);
    }
    close(pipe2[0]); close(pipe2[1]);

    // Process 4: awk '{print $2}'
    pids[3] = fork();
    if (pids[3] < 0) {
        perror("fork awk");
        return 1;
    } else if (pids[3] == 0) {
        dup2(pipe3[0], STDIN_FILENO);
        close(pipe3[0]); close(pipe3[1]);
        char* args[] = {(char*)"awk", (char*)"{print $2}", NULL};
        execvp("awk", args);
        perror("exec awk");
        exit(1);
    }
    close(pipe3[0]); close(pipe3[1]);

    // Wait for all child processes to complete
    for (int i = 0; i < 4; ++i) {
        if (waitpid(pids[i], NULL, 0) == -1) {
            perror("waitpid failed");
        }
    }

    return 0;
}

