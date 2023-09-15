#include "minishell.h"

static int is_accessible(char **bin, char *tmp, char *cmd)
{
    int i;
    int valid;

    i = 0;
    valid = 0;
    while (bin[i])
    {
        bin[i][ft_strlen(bin[i])] = '/';
        tmp = ft_strjoin(bin[i], cmd);
        if ((access(tmp, F_OK | X_OK)) == 0)
            valid = 1;   
        i++;
        free(tmp);
    }
    return (valid);
}

int find_env(char *cmd)
{
    char *env;
    char **bin;
    int i;
    char *tmp;
    int valid;

    env = getenv("PATH");
    bin = ft_split(env, ':');

    if((is_accessible(bin, tmp,cmd)) == 0)
    {
        free_array(bin);
        printf("command not found");
        return (-1);
    }
    free_array(bin);
    return (0);
}