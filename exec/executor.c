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

int outfiler(char **outfiles, char *tokens, int flags)
{
    int i;
    int fd;

    i = -1;
    
    while (tokens[++i] == '>' && outfiles[i] != NULL)
        fd = open(outfiles[i], flags, 0777);
    return(fd);
}

void first_process(t_data data,char *t, int *fd, int i)
{
    printf("%s\n", t);
    if (t[0] == '|')
    {
        dup2(fd[1], STDOUT_FILENO);
    }
    else if (t[0] == '>' && t[1] == '\0')
    {
        dup2(outfiler(data.nodes[i].outfile, data.operators[i], O_WRONLY | O_CREAT), STDOUT_FILENO);
    }
    else if (t[0] == '>' && t[1] == '>')
    {
        dup2(outfiler(data.nodes[i].outfile, data.operators[i], O_WRONLY | O_CREAT | O_APPEND), STDOUT_FILENO);
    }
    else if (t[0] == '<' && t [1] == '<')
    {
        char buffer[256];
        ssize_t bytes_read;
        while (1)
        {
            bytes_read = read(STDIN_FILENO, buffer, sizeof(buffer));
            buffer[bytes_read] = '\0';
            if (ft_strncmp(buffer, data.nodes[i].infile[0], ft_strlen(data.nodes[i].infile[0])) == 0) 
            {
                break;
            }
        }    
    }
    else
    {
        printf("im waiting\n");
        //waitpid(pid, NULL, WUNTRACED);
    }
}

void close_fds(int *fd, int *fd2)
{
    if (fd != NULL)
    {
        printf("here3\n");
        close(fd[0]);
        close(fd[1]);
    }
    if (fd2 != NULL)
    {
        printf("here4\n");
        close(fd2[0]);
        close(fd2[1]);
    }
}

void router(t_data data, int i, int *fd, int *fd2)
{
    if(i >= 1)
    {
        close(fd[1]);
        dup2(fd[0], STDIN_FILENO);
        close(fd[0]);
        if (fd2 != NULL)
        {
            close(fd2[0]);
            dup2(fd2[1], STDOUT_FILENO);
        }
        first_process(data,data.operators[i],fd ,i);
    }
    else 
    {
        if (fd != NULL)
        {
            close(fd[0]);
        }
        first_process(data, data.operators[i], fd, i);
    }
    //close_fds(fd, fd2);
    printf("ended *%s* *%s*\n", data.nodes[i].args[0], data.nodes[i].args[1]);
    execve(data.nodes[i].args[0], data.nodes[i].args, NULL);
}

pid_t *pid_create(int size)
{
    pid_t *tmp;
    tmp = (pid_t *)malloc(sizeof(pid_t) * size);
    return(tmp);
}

int executor(t_data data)
{
    if((find_env(data)) == -1)
        return -1;

    int **pipes;
    pipes = pipe_create(data.pipe_count);
    int i = -1;
    pid_t *pids;
    pids = pid_create(data.pipe_count + 1);

    while (++i < (data.pipe_count + 1))
    {
        pids[i] = fork();
        if (pids[i] == 0)
        {
            router(data, i, pipes[(i / 2)], pipes[(i / 2) + 1]);
            exit(0);
        }
        // if (data.pipe_count > 0)
        //     close(pipes[(i / 2)][1]);
    }
    close_pipes(pipes, data.pipe_count);
    i = -1;
    while (++i < data.pipe_count + 1)
    {
        waitpid(pids[i], NULL, WUNTRACED);
    }
    free(pids);
    return 0;
}