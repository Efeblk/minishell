#include "minishell.h"

static void is_builtin(char *cmd, t_data *data, int i, t_env *env)
{
    if (ft_strncmp(cmd, "clear", 5) == 0)
        printf("\033[2J\033[H");
    if (ft_strncmp(cmd, "exit", 4) == 0)
        run_exit(data);
    else if (ft_strncmp(cmd, "pwd", 3) == 0)
        run_pwd();
    //else if(ft_strncmp(cmd, "cd", 2) == 0)
        //run_cd(NULL);
    else if (ft_strncmp(cmd, "echo", 4) == 0)
        run_echo(data, i);
    else if (ft_strncmp(cmd, "env", 3) == 0)
        run_env(env);
    // else if (ft_strncmp(cmd, "export", 6) == 0)
    //     run_export(env, i, data);
    else
        printf("no builtin \n"); //burası önemli else olmayınca TERM error basıyor?
}

void built_in(t_data *data, char *envp[], t_env *env)
{
    (void)envp;
    int i;

    i = -1;
    while (++i < (data->pipe_count + 1))
    {
        is_builtin(data->nodes[i].cmd, data, i, env);
    }
}

