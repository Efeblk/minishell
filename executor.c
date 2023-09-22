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
    while (tokens[++i] == '>')
        fd = open(outfiles[i], flags, 0777);
    return(fd);
}

void first_process(t_data data,char *t, int *fd, int i)
{
    if (t[0] == '|')
    {
        dup2(fd[1], STDOUT_FILENO);
    }
    else if (t[0] == '>')
    {
        dup2(outfiler(data.nodes[i].outfile, data.tokens[i], O_WRONLY | O_CREAT), STDOUT_FILENO);
    }
    else if (t[0] == '>' && t[1] == '>')
    {
        dup2(outfiler(data.nodes[i].outfile, data.tokens[i], O_WRONLY | O_CREAT | O_APPEND), STDOUT_FILENO);
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
        dup2(fd[0], STDIN_FILENO);
        if (fd2 != NULL)
        {
            close(fd2[0]);
            dup2(fd2[1], STDOUT_FILENO);
        }
        first_process(data,data.tokens[i],fd ,i);
    }
    else 
    {
        //write(STDIN_FILENO, "q", 2);
        first_process(data, data.tokens[i], fd, i);
    }
    close_fds(fd, fd2);
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
        if (data.pipe_count > 0)
            close(pipes[(i / 2)][1]);
    }
    i = -1;
    while (++i < data.pipe_count + 1)
    {
        waitpid(pids[i], NULL, WUNTRACED);
    }
    close_pipes(pipes, data.pipe_count);
    free(pids);
    return 0;
}

int main(int argc, char const *argv[])
{
    t_data data;

    data.nodes =(t_node *)malloc(sizeof(t_node) * 3);

    data.nodes[0].cmd = (char *)malloc(sizeof(char) * 3);
    data.nodes[0].args = (char **)malloc(sizeof(char *) * 3);
    data.nodes[0].args[1] = (char *)malloc(sizeof(char) * 3);

    data.nodes[0].cmd = "ls\0";
    data.nodes[0].args[1] = "-l\0";
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
    data.nodes[2].args[1] = (char *)malloc(sizeof(char) * 4);

    data.nodes[2].cmd = "ls\0";
    data.nodes[2].args[1] = "-la\0";
    data.nodes[2].args[2] = NULL;

    ////////////////////////////////////////////////////////////
    data.tokens = (char **)malloc(sizeof(char *) * 4);
    data.tokens[0] = (char *)malloc(sizeof(char) * 2);
    data.tokens[1] = (char *)malloc(sizeof(char) * 3);
    data.tokens[2] = (char *)malloc(sizeof(char) * 3);
    data.tokens[3] = (char *)malloc(sizeof(char) * 1);

    data.pipe_count = 2;

    data.tokens[0][0] = '|';
    data.tokens[0][1] = '\0';

    data.tokens[1][0] = '|';
    data.tokens[1][1] = '\0';

    data.tokens[2][0] = '>';
    data.tokens[2][1] = '>';
    data.tokens[2][2] = '\0';

    data.tokens[3][0]= '\0';

    data.nodes[2].outfile = malloc(sizeof(char *) * 2);
    data.nodes[2].outfile[0] = malloc(sizeof(char) * 2);
    data.nodes[2].outfile[1] = malloc(sizeof(char) * 2);

    data.nodes[2].outfile[0] = "a\0";
    data.nodes[2].outfile[1] = "b\0";

    //char *a[] = { "/bin/cat", NULL};
    // execve(a[0], a, NULL);
    // printf("asjdnjasd");
    executor(data);
    //system("leaks main");
    return 0;
}