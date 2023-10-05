#include "minishell.h"

static void question_mark(t_data *data, t_globals *globals)
{
    int i;
    int j;
    int flag;

    j = 1;
    i = 0;
    flag = 0;

    while (i < data->pipe_count + 1)
    {
        if (data->nodes[i].cmd != NULL)
        {
            if (data->nodes[i].cmd[0] == '$' && data->nodes[i].cmd[1] == '?')
            {
                flag = 1;
                printf("%i: ", globals->status);
                break;
            }
        }    
        else
        {
            while (data->nodes[i].args[j] != NULL)
            {
                if (data->nodes[i].args[j][0] == '$' && data->nodes[i].args[j][1] == '?')
                    printf("%i", globals->status);
                j++;
            }
        }   
        i++;  
    }
}
static void is_builtin(char *cmd, t_data *data, int i, t_globals *globals, t_env **env, t_export **exp_list)
{
    question_mark(data, globals);
    if (cmd != NULL)
    {
        if (ft_strncmp(cmd, "clear", 5) == 0)
            printf("\033[2J\033[H");
        else if (ft_strncmp(cmd, "exit", 4) == 0)
            run_exit(data);
        else if (ft_strncmp(cmd, "pwd", 3) == 0)
            run_pwd();
        else if(ft_strncmp(cmd, "cd", 2) == 0)
            run_cd(data, i);
        else if (ft_strncmp(cmd, "echo", 4) == 0)
            run_echo(data, i);
        else if (ft_strncmp(cmd, "env", 3) == 0)
            run_env(*env);
        else if (ft_strncmp(cmd, "export", 6) == 0)
            run_export(exp_list, i, data, env);
        else
        {
            data->nodes[i].is_builtin = 0;
        }
    }
}

void built_in(t_data *data, t_globals *globals, t_env **env, t_export **exp_list)
{
    //(void)envp;
    int i;

    i = -1;
    while (++i < data->pipe_count + 1)
    {
        is_builtin(data->nodes[i].cmd, data, i, globals, env, exp_list);
        if (data->nodes[i].is_builtin == 1)
            globals->status = 0;
        
    }
}

