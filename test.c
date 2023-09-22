#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    int pipe_fd[2];
    
    if (pipe(pipe_fd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid_t child_pid = fork();

    if (child_pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (child_pid == 0) {
        // This is the child process
        close(pipe_fd[1]);  // Close the write end of the pipe

        // Redirect the read end of the pipe to stdin
        dup2(pipe_fd[0], STDIN_FILENO);
        close(pipe_fd[0]);

        // Execute a command that reads from stdin (in this case, no specific command)
        char *command_args[] = {"/bin/cat", NULL}; // You can use any command that reads from stdin
        char *command_env[] = {NULL};
        
        if (execve("/bin/cat", command_args, command_env) == -1) {
            perror("execve");
            exit(EXIT_FAILURE);
        }
    } else {
        // This is the parent process
        close(pipe_fd[0]);  // Close the read end of the pipe

        // Redirect stdout to the write end of the pipe
        dup2(pipe_fd[1], STDOUT_FILENO);
        close(pipe_fd[1]);

        // Execute 'cat' in the parent process
        char *cat_args[] = {"cat", "file.txt", NULL}; // Replace "file.txt" with your desired file
        char *cat_env[] = {NULL};
        
        if (execve("/bin/cat", cat_args, cat_env) == -1) {
            perror("execve");
            exit(EXIT_FAILURE);
        }
    }
    wait(&child_pid);

    return 0;
}
