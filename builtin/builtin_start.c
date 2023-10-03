#include "minishell.h"

static void is_builtin(char *cmd, t_data *data, int i)
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
    else
        printf("no builtin \n"); //burası önemli else olmayınca TERM error basıyor?
}

void built_in(t_data *data)
{
    int i;

    i = -1;
    while (data->nodes[++i].cmd != NULL)
    {
        is_builtin(data->nodes[i].cmd, data, i);
    }
}

