#include "minishell.h"

static void first_process(t_data *data, int **pipes, int i)
{
    if (data->pipe_count > 0)
    {
        dup2(pipes[0][1], STDOUT_FILENO);
    }
    close_pipes(pipes, data->pipe_count);
    op_router(data, i);
}

static void middle_process(t_data *data, int **pipes, int i)
{
    dup2(pipes[i - 1][0], STDIN_FILENO);
    dup2(pipes[i][1], STDOUT_FILENO);
    close_pipes(pipes, data->pipe_count);
    op_router(data, i);
}

static void last_process(t_data *data, int **pipes, int i)
{
    dup2(pipes[i - 1][0], STDIN_FILENO);
    close_pipes(pipes, data->pipe_count);
    op_router(data, i);
}

static void wait_close_free(t_data *data, int **pipes, int *pids, t_globals *globals)
{
    int i;

    close_pipes(pipes, data->pipe_count);
    i = -1;
    while (++i < data->pipe_count + 1)
    {
        if (data->nodes[i].is_builtin == 0 && data->nodes[i].is_valid_cmd == 1)
        {
            if (waitpid(pids[i], &globals->status, 0) == -1)
            {
                perror("waitpid");
            }
        }
    }
    free(pids);
}

int executor(t_data *data, t_globals *globals, char **env)
{
    int **pipes;
    pid_t *pids;
    int i;

    find_env(data, globals);
    i = -1;
    pipes = pipe_create(data->pipe_count);
    pids = pid_create(data->pipe_count + 1);
    while (++i < (data->pipe_count + 1))
    {
        if (data->nodes[i].is_builtin == 0)
        {
            pids[i] = fork();
            if (pids[i] == 0)
            {
                if (i == 0)
                    first_process(data, pipes, i);
                else if (i == data->pipe_count)
                    last_process(data, pipes, i);
                else
                    middle_process(data, pipes, i);
                globals->status = 0;
                //printf("exec \n");
                execve(data->nodes[i].args[0], data->nodes[i].args, env);
                exit(0);
            }
        }
    }
    wait_close_free(data, pipes, pids, globals);
    return 0;
}