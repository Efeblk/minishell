#include "minishell.h"

static int is_accessible(char **bin, t_data data)
{
    int i;
    int j;
    int valid;
    char *tmp;
    char *path;

    valid = 0;
    j = -1;
    while (++j < (data.pipe_count + 1))
    {
        i = -1;
        while (bin[++i])
        {
            if (bin[i][ft_strlen(bin[i]) - 1] != '/')
                bin[i][ft_strlen(bin[i])] = '/';
            tmp = ft_strjoin(bin[i], data.nodes[j].cmd);
            //is accessible?
            if ((access(tmp, F_OK | X_OK)) == 0)
            {
                data.nodes[j].args[0] = (char *)malloc(sizeof(char) * ft_strlen(tmp) + 1);
                path = ft_strdup(tmp);
                data.nodes[j].args[0] = path;
                valid += 1;
            }
            free(tmp);
        }
        
    }
    return (valid);
}

int find_env(t_data data)
{
    char *env;
    char **bin;
    
    env = getenv("PATH");
    bin = ft_split(env, ':');

    if((is_accessible(bin, data) < data.pipe_count + 1))
    {
        free_array((void **)bin);
        printf("command not found");
        return (-1);
    }
    free_array((void **)bin);
    return (0);
}