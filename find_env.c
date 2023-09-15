#include "minishell.h"

static int is_accessible(char **bin, t_node *node)
{
    int i;
    int valid;
    char *tmp;
    char *path;
    i = 0;
    valid = 0;
    while (bin[i])
    {
        bin[i][ft_strlen(bin[i])] = '/';
        tmp = ft_strjoin(bin[i], node->cmd);
        if ((access(tmp, F_OK | X_OK)) == 0)
        {
            node->args[0] = (char *)malloc(sizeof(char) * ft_strlen(tmp) + 1);
            path = ft_strdup(tmp);
            node->args[0] = path;
            valid = 1;
        }
        i++;
        free(tmp);
    }
    return (valid);
}

int find_env(t_data data)
{
    char *env;
    char **bin;
    
    env = getenv("PATH");
    bin = ft_split(env, ':');

    if((is_accessible(bin, data.nodes)) == 0)
    {
        free_array(bin);
        printf("command not found");
        return (-1);
    }
    free_array(bin);
    return (0);
}