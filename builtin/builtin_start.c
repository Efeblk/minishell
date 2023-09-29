#include "minishell.h"

static void is_builtin(char *cmd)
{
    if (ft_strncmp(cmd, "clear", 5) == 0)
    {
        printf("\033[2J\033[H");
        
    }   
    if (ft_strncmp(cmd, "exit", 4) == 0)
    {
        printf("exit");
        exit(0);
    }
    if (ft_strncmp(cmd, "pwd", 3) == 0)
    {
        char	*s;
        s = getcwd(NULL, 0);
        if (!s)
        {
            perror("tsh: pwd getcwd error");
            exit(1);
        }
        else
            printf("%s\n", s);
        free(s);
        exit(0);
    }
}

void built_in(t_data *data)
{
    int i;

    i = -1;

    while (data->nodes[++i].cmd != NULL)
    {
        printf("CMD %s\n", data->nodes[i].cmd);
        is_builtin(data->nodes->cmd);
    }
}

