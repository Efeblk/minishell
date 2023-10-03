#include "minishell.h"

int **pipe_create(int pipe_count)
{
    int i;
    int **pipes;

    i = -1;
    if (pipe_count == 0)
    {
        pipes = (int **)malloc(sizeof(int *) * 2);
        if (pipes == NULL)
        {
            perror("malloc");
            return NULL;
        }
        pipes[0] = NULL;
        pipes[1] = NULL;
        return pipes;
    }

    pipes = (int **)malloc(sizeof(int *) * (pipe_count + 1));
    if (pipes == NULL)
    {
        perror("malloc");
        return NULL;
    }
    while (++i < pipe_count)
    {
        pipes[i] = (int *)malloc(sizeof(int) * 2);
        if (pipes[i] == NULL)
        {
            perror("malloc");
            return NULL;
        }
        if(pipe(pipes[i]) == -1)
        {
            perror("pipe");
            return NULL;
        }
    }
    pipes[i] = NULL;
    return (pipes);
}

void close_pipes(int **pipes, int pipe_count)
{
    int i = 0;
    while (i < pipe_count)
    {
        close(pipes[i][0]);
        close(pipes[i][1]);
        free(pipes[i]);
        i++;
    }
    free(pipes);
}

pid_t *pid_create(int size)
{
    pid_t *tmp;
    tmp = (pid_t *)malloc(sizeof(pid_t) * size);
    return(tmp);
}