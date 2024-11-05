//Name:Siri Nandipaty student id:21449384

#include <string.h>
#include <stdio.h>
#include <dirent.h>
#include <sys/wait.h>
#include <stdlib.h>
#define MAX_BUFFER 1024                        
#define MAX_ARGS 64                            
#define SEPARATORS " \t\n"

void execute_command(char **args) {
    pid_t pid;
    int status;
    int input_fd, output_fd;
    char *input_file, *output_file;
    int background = 0;

    // check if the command should run in the background
    for (int i = 0; args[i] != NULL; i++) {
        if (strcmp(args[i], "&") == 0) {
            background = 1;
            args[i] = NULL;
            break;
        }
    }

    // look for input/output redirection symbols
    input_file = NULL;
    output_file = NULL;
    for (int i = 0; args[i] != NULL; i++) {
        if (strcmp(args[i], "<") == 0) {
            input_file = args[i+1];
            args[i] = NULL;
        } else if (strcmp(args[i], ">") == 0) {
            output_file = args[i+1];
            args[i] = NULL;
        }
    }

    // open input/output files if specified
    if (input_file != NULL) {
        input_fd = open(input_file, O_RDONLY);
        if (input_fd == -1) {
            perror("Error opening input file");
            return;
        }
        dup2(input_fd, STDIN_FILENO);
        close(input_fd);
    }
    if (output_file != NULL) {
        output_fd = open(output_file, O_WRONLY|O_CREAT|O_TRUNC, 0644);
        if (output_fd == -1) {
            perror("Error opening output file");
            return;
        }
        dup2(output_fd, STDOUT_FILENO);
        close(output_fd);
    }

    // fork a new process
    pid = fork();
    setenv("parent", "/myshell", 1);
    if (pid == -1) {
        perror("Error forking process");
        return;
    } else if (pid == 0) {
        // child process: execute the command
        execvp(args[0], args);
        perror("Error executing command");
        exit(EXIT_FAILURE);
    } else {
        // parent process: wait for the child to finish (if not running in background)
        if (!background) {
            waitpid(pid, &status, 0);
        }
    }
}
