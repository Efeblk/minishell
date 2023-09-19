#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv, char **envp) {
    int fd[2];
    char asd[5]; // Allocate memory for asd, including space for the null terminator

    if (pipe(fd) == -1) {
        perror("pipe");
        return 1;
    }
    write(fd[1], "abc\n", 5);
    // Close the write end of the pipe in the parent
    close(fd[1]);

    
    ssize_t bytesRead = read(fd[0], asd, sizeof(asd) - 1);
    if (bytesRead == -1) {
        perror("read");
        return 1;
    }

    asd[bytesRead] = '\0'; // Null-terminate the string
    printf("%s\n", asd);

    // Close the read end of the pipe in the parent
    close(fd[0]);

    return 0;
}
