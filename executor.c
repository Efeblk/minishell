#include "minishell.h"

int **pipe_create(int pipe_count)
{
    int i;
    int **pipes;

    i = -1;

    if (pipe_count == 0)
    {
        pipes = (int **)malloc(sizeof(int *) * 2);
        pipes[0] = NULL;
        pipes[1] = NULL;
        return pipes;
    }

    pipes = (int **)malloc(sizeof(int *) * (pipe_count + 1));
    while (++i < pipe_count)
    {
        pipes[i] = (int *)malloc(sizeof(int) * 2);
        if(pipe(pipes[i]) == -1)
        {
            printf("pipe error \n");
        }
    }
    pipes[i] = NULL;
    return (pipes);
}

void router(t_data data, int i, int *fd, int *fd2)
{
    if(i >= 1)
    {
        dup2(fd[0], STDIN_FILENO);
        if (fd2 != NULL && data.tokens[i][0] == '|')
        {
            close(fd2[0]);
            dup2(fd2[1], STDOUT_FILENO);
        }
    }
    else if (data.tokens[i][0] == '|')
    {    
        dup2(fd[1], STDOUT_FILENO);
    }
    if (fd != NULL)
    {
        close(fd[0]);
        close(fd[1]);
    }
    if (fd2 != NULL)
    {
        close(fd2[0]);
        close(fd2[1]);
    }
    execve(data.nodes[i].args[0], data.nodes[i].args, NULL);
}

int executor(t_data data)
{
    if((find_env(data)) == -1)
        return -1;

    int **pipes;
    pipes = pipe_create(data.pipe_count);
    int i = -1;
    pid_t pid;

    while (++i < (data.pipe_count + 1))
    {
        pid = fork();
        if (pid == 0)
        {
            router(data, i, pipes[(i / 2)], pipes[(i / 2) + 1]);
            exit(0);
        }
        if (data.pipe_count > 0)
            close(pipes[(i / 2)][1]);
        
        waitpid(pid, NULL, WUNTRACED);
    }
    close_pipes(pipes, data.pipe_count);
    return 0;
}

int main(int argc, char const *argv[])
{
    t_data data;

    data.nodes =(t_node *)malloc(sizeof(t_node) * 3);
    data.nodes[0].cmd = (char *)malloc(sizeof(char) * 3);
    data.nodes[0].args = (char **)malloc(sizeof(char *) * 3);
    data.nodes[0].args[1] = (char *)malloc(sizeof(char) * 4);

    data.nodes[0].cmd = "ls\0";
    data.nodes[0].args[1] = "-la\0";
    data.nodes[0].args[2] = NULL;

    //////////////////////////////////////////////////////////
    data.nodes[1].cmd = (char *)malloc(sizeof(char) * 5);
    data.nodes[1].args = (char **)malloc(sizeof(char *) * 3);
    data.nodes[1].args[1] = (char *)malloc(sizeof(char) * 4);

    data.nodes[1].cmd = "grep\0";
    data.nodes[1].args[1] = "git\0";
    data.nodes[1].args[2] = NULL;

    /////////////////////////////////////////////////////////
    data.nodes[2].cmd = (char *)malloc(sizeof(char) * 3);
    data.nodes[2].args = (char **)malloc(sizeof(char *) * 3);
    data.nodes[2].args[1] = (char *)malloc(sizeof(char) * 2);

    data.nodes[2].cmd = "wc\0";
    data.nodes[2].args[1] = "-l\0";
    data.nodes[2].args[2] = NULL;

    ////////////////////////////////////////////////////////////
    data.tokens = (char **)malloc(sizeof(char *) * 2);
    data.tokens[0] = (char *)malloc(sizeof(char) * 2);
    data.tokens[1] = (char *)malloc(sizeof(char) * 2);

    data.pipe_count = 2;

    data.tokens[1][0] = '|';
    data.tokens[1][1] = '\0';
    data.tokens[0][1] = '\0';
    data.tokens[0][0] = '|';

    executor(data);
    //system("leaks main");
    return 0;
}
