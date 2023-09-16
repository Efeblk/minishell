#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include  <fcntl.h>

int main(int ac, char **av, char **env)
{
    int     fd[2];
    pid_t   pid;
    pipe(fd);

    pid = fork();
    if (pid == 0)
    {
        int fd1 = open("test.txt", O_WRONLY | O_CREAT, 0777);
        dup2(fd1, STDOUT_FILENO);
        write(1, "-42\n", 4);
        close(fd[0]);
        close(fd[1]);
        close(fd1);
        exit(0);
    }
    else
    {
        waitpid(pid, NULL, WUNTRACED);
    }
}