#include "minishell.h"

static int question_mark(t_data *data, t_env **env)
{
    int i;
    int j;
    int flag;
    int status;
    char *tmp;

    flag = 0;
    j = 1;
    i = 0;
    tmp = get_env_val("?", *env);
    status = ft_atoi(tmp);
    
    while (i < data->pipe_count + 1)
    {
        if (data->nodes[i].cmd != NULL)
        {
            if (data->nodes[i].cmd[0] == '$' && data->nodes[i].cmd[1] == '?')
            {
                flag = 1;
                printf("TMP : %i \n", status);
                if (status > 255)
                {
                    status = status % 255;
                    update_status(status, env);
                }
                printf("%i: ", status);
                break;
            }
        }
        else
        {
            while (data->nodes[i].args[j] != NULL)
            {
                if (data->nodes[i].args[j][0] == '$' && data->nodes[i].args[j][1] == '?')
                {
                    flag = 1;
                    printf("TMP : %i \n", status);
                    if (status > 255)
                    {
                        status = status % 255;
                        update_status(status, env);
                    }
                    printf("%i: ", status);
                    break;
                }
                if (flag)
                    break;
                j++;
            }
        }
        i++;
    }
    return(flag);
}

static void is_builtin(char *cmd, t_data *data, int i, t_env **env, t_export **exp_list)
{
    int flag;

    data->nodes[i].is_builtin = 1;
    flag = question_mark(data, env);
    if (cmd != NULL)
    {
        if (flag == 1)
            ;
        else if (ft_strncmp(cmd, "clear", 5) == 0)
            printf("\033[2J\033[H");
        else if (ft_strncmp(cmd, "exit", 4) == 0)
            run_exit(data, env, i);
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
        else if (ft_strncmp(cmd, "unset", 5) == 0)
            run_unset(env, exp_list, i, data);
        else
        {
            data->nodes[i].is_builtin = 0;
        }
    }
}

void built_in(t_data *data, t_env **env, t_export **exp_list)
{
    int i;

    i = -1;
    while (++i < data->pipe_count + 1)
    {
        is_builtin(data->nodes[i].cmd, data, i, env, exp_list);
        if (data->nodes[i].is_builtin == 1)
            update_status(0, env);
    }
}

