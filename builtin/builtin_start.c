#include "minishell.h"

static void is_builtin(char *cmd)
{
    if (ft_strncmp(cmd, "clear", 5) == 0)
    {
        printf("ıaosdnıaos \n ");
        printf("\033[2J\033[H");
        
    }
        
    if (ft_strncmp(cmd, "exit", 4) == 0)
    {
        /* code */
    }
    

}

void built_in(t_data *data)
{
    int i;

    i = -1;

    while (data->nodes[++i].cmd != NULL)
    {
        printf("asdasd %s\n", data->nodes[i].cmd);
        is_builtin(data->nodes->cmd);
    }
}

