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
        (*j)++;
    }
    (*j)--;
    return(fd);
}

void first_process(t_data *data, int i)
{

    int j = -1;
    while (data->nodes[i].operators[++j] != NULL)
    {
        if (ft_strncmp(data->nodes[i].operators[j], ">", 1) == 0)
        {
            dup2(outfiler(data->nodes[i].outfile, data->nodes[i].operators, &j), STDOUT_FILENO);
        }
        else if (ft_strncmp(data->nodes[i].operators[j], ">>", 2) == 0)
        {
            dup2(outfiler(data->nodes[i].outfile, data->nodes[i].operators, &j), STDOUT_FILENO);
        }
        else if (ft_strncmp(data->nodes[i].operators[j], "<<", 2) == 0)
        {
            // Create a temporary file
            FILE *tmp = tmpfile();
            char buffer[1024];
            char *delimiter = data->nodes[i].infile[0];

            // Read from stdin until the delimiter is found
            while (fgets(buffer, sizeof(buffer), stdin) != NULL)
            {
                if (strncmp(buffer, delimiter, strlen(delimiter)) == 0)
                    break;
                fputs(buffer, tmp);
            }

            // Redirect stdin to the temporary file
            fflush(tmp);
            rewind(tmp);
            dup2(fileno(tmp), STDIN_FILENO);

            // Execute the command
            execve(data->nodes[i].args[0], data->nodes[i].args, NULL);
        }
    }
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

int executor(t_data *data)
{
    find_env(data);

    int **pipes;
    pipes = pipe_create(data->pipe_count);
    if (pipes == NULL)
    {
        return -1;
    }
    int i = -1;
    pid_t *pids;
    pids = pid_create(data->pipe_count + 1);
    if (pids == NULL)
    {
        return -1;
    }

    while (++i < (data->pipe_count + 1))
    {
        pids[i] = fork();
        if (pids[i] == -1)
        {
            perror("fork");
            return -1;
        }
        if (pids[i] == 0)
        {
            if (i == 0)
            {
                // First command
                if (data->pipe_count > 0)
                {
                    dup2(pipes[0][1], STDOUT_FILENO);
                }
                close_pipes(pipes, data->pipe_count);
                first_process(data, i);
            }
            else if (i == data->pipe_count)
            {
                // Last command
                dup2(pipes[i - 1][0], STDIN_FILENO);
                close_pipes(pipes, data->pipe_count);
                first_process(data, i);
            }
            else
            {
                // Middle commands
                dup2(pipes[i - 1][0], STDIN_FILENO);
                dup2(pipes[i][1], STDOUT_FILENO);
                close_pipes(pipes, data->pipe_count);
                first_process(data, i);
            }
            execve(data->nodes[i].args[0], data->nodes[i].args, NULL);
            exit(0);
        }
    }

    close_pipes(pipes, data->pipe_count);
    i = -1;
    while (++i < data->pipe_count + 1)
    {
        if (waitpid(pids[i], NULL, 0) == -1)
        {
            perror("waitpid");
        }
    }
    free(pids);
    return 0;
}