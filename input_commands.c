#include "minishell.h"

int is_input(char *cmd)
{
    if (ft_strncmp(cmd, "wc", 2) == 0)
        return(1);
    else if (ft_strncmp(cmd, "cat", 3) == 0)
        return(1);
    return 0;
}