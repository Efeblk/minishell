#include "minishell.h"

static int is_executable(char **bin, t_data *data, int *valid, int *j)
{
    int i;
    char *tmp;

    i = -1;
    while (bin[++i])
    {
        if (bin[i][ft_strlen(bin[i]) - 1] != '/')
            bin[i][ft_strlen(bin[i])] = '/';
        tmp = ft_strjoin(bin[i], data->nodes[*j].cmd); 
        
        if ((access(tmp, F_OK | X_OK)) == 0)
        {
            data->nodes[*j].args[0] = ft_strdup(tmp);
            *valid += 1;
            free(tmp);
            return (1);
        }
        free(tmp);
    }
    return (0);
}

static int is_path(t_data *data, int *valid, int *j)
{
    if (data->nodes[*j].cmd != NULL && data->nodes[*j].cmd[0] == '/')
    {
        data->nodes[*j].args[0] = ft_strdup(data->nodes[*j].cmd);
        *valid += 1;
        return(1);
    }
    else if (data->nodes[*j].cmd[0] == '.' && data->nodes[*j].cmd[1] == '/')
    {
        data->nodes[*j].args[0] = ft_strdup(data->nodes[*j].cmd);
        *valid += 1;
        return(1);
    }
    return (0);
}

static int is_accessible(char **bin, t_data *data)
{
    int j;
    int valid;
    
    valid = 0;
    j = -1;
    while (++j < (data->pipe_count + 1))
    {
        if (data->nodes[j].cmd != NULL)
        {
            if (!is_executable(bin, data, &valid, &j) && !is_path(data, &valid, &j))
            {
                printf("here\n");
                data->nodes[j].args[0] = ft_strdup(data->nodes[j].cmd);
            }   
            printf("%s \n", data->nodes[j].args[0]);
            printf("%s \n", data->nodes[j].args[1]);
        }
        else if (data->nodes[j].cmd == NULL)
            valid += 1;
    }
    return (valid);
}

int find_env(t_data *data, t_globals *globals)
{
    char *env;
    char **bin; 
    
    env = getenv("PATH");
    bin = ft_split(env, ':');

    if((is_accessible(bin, data) < data->pipe_count + 1))
    {
        free_array((void **)bin);
        printf("command not found\n");
        globals->status = 127;
        return (127);
    }
    free_array((void **)bin);
    return (0);
}