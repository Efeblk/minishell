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

int outfiler(char **outfiles, char **operators, int *j)
{
    int i;
    int fd;

    i = -1;

    while (outfiles[++i] && (((ft_strncmp(operators[i], ">", 1)) == 0) || ((ft_strncmp(operators[i], ">>", 2)) == 0)))
    {
        if ((ft_strncmp(operators[i], ">", 2)) == 0)
        {
            //printf("here > : %s\n", operators[i]);
            fd = open(outfiles[i], O_WRONLY | O_CREAT | O_TRUNC , 0777);
        }
        else if ((ft_strncmp(operators[i], ">>", 2)) == 0)
        {
            //printf("here >> : %s\n", operators[i]);
            fd = open(outfiles[i], O_WRONLY | O_CREAT | O_APPEND, 0777);
        }
        printf("q %s\n", operators[*j]);
        (*j)++;
        printf("qq %s\n", operators[*j]);
    }
    (*j)--;
    printf("while %i \n", *j);
    printf("qqq %s\n", operators[*j]);
    return(fd);
}

void first_process(t_data data, int i)
{
    //printf("ansdkasbndjkasbdjkl %s \n", t);
    //printf("first process *%s* *%s*\n", data.nodes[i].args[0], data.nodes[i].args[1]);
    //if(data.nodes[i].is_pipe == 1)
    int j = -1;
    while (data.nodes[i].operators[++j] != NULL)
    {
        printf("TTTTT %i \n", j);
        if (ft_strncmp(data.nodes[i].operators[j], ">", 1) == 0)
        {
            //printf("   2   \n");
            dup2(outfiler(data.nodes[i].outfile, data.nodes[i].operators, &j), STDOUT_FILENO);
        }
        else if (ft_strncmp(data.nodes[i].operators[j], ">>", 2) == 0)
        {
            //printf("   3   \n");
            dup2(outfiler(data.nodes[i].outfile, data.nodes[i].operators, &j), STDOUT_FILENO);
        }
        else if (ft_strncmp(data.nodes[i].operators[j], "<<", 2) == 0)
        {
            while (1)
            {
                char *buffer;
                buffer = readline(">");
                if (buffer && ft_strncmp(buffer, data.nodes[i].infile[0], ft_strlen(buffer)) == 0) 
                {
                    printf("break\n");
                    break;
                }
                free(buffer);
            }    
        }
    }
    //printf("first_process end \n");
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
    //printf("start %s %s \n", data.nodes[i].args[0], data.nodes[i].args[1]);
    if(i >= 1)
    {
        close(fd[1]);
        dup2(fd[0], STDIN_FILENO);
        if (data.nodes[i].is_pipe == 1)
        {
            close(fd2[0]);
            dup2(fd2[1], STDOUT_FILENO); printf("uc degisti \n");
        }
        first_process(data, i);
    }
    else 
    {
        if (fd != NULL)
        {
            close(fd[0]);
            dup2(fd[1], STDOUT_FILENO); printf("uc degisti \n");
        }
        first_process(data, i);
    }
    //close_fds(fd, fd2);
    //printf("ended *%s* *%s*\n", data.nodes[i].args[0], data.nodes[i].args[1]);
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

    //printf("EXECCCC %s\n", data2.nodes[0].cmd);
    //printf("EXECCCC %s\n", data.nodes[0].args[1]);
    //data.nodes[0].args[2] = NULL;
    //printf("EXECCCC %s\n", data.nodes[0].args[2]);
    find_env(data);
        //return -1;

    //printf("EXECCCC %s\n", data2.nodes[0].args[0]);
    //printf("EXEC pipe count %i \n", data2.pipe_count);
    // data.operators = (char **)malloc(sizeof(char *) * 1);
    // data.operators[0] = (char *)malloc(sizeof(char) * 1);
    // data.operators[0][0] = '\0';
    //printf("ops.ç %c",  data.operators[0][0]);

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
        waitpid(pids[0], NULL, WUNTRACED);
    }
    free(pids);
    return 0;
}