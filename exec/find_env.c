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
    if (data->nodes[*j].is_builtin == 0)
        data->nodes[*j].is_valid_cmd = 0;
    return (0);
}

static int is_path(t_data *data, int *valid, int *j)
{
    if (data->nodes[*j].cmd != NULL && data->nodes[*j].cmd[0] == '/')
    {
        data->nodes[*j].is_valid_cmd = 1;
        data->nodes[*j].args[0] = ft_strdup(data->nodes[*j].cmd);
        *valid += 1;
        return(1);
    }
    else if (data->nodes[*j].cmd[0] == '.' && data->nodes[*j].cmd[1] == '/')
    {
        data->nodes[*j].is_valid_cmd = 1;
        //char *c = return_pwd();
        data->nodes[*j].args[0] = ft_strdup(data->nodes[*j].cmd);
        *valid += 1;
        return(1);
    }
    if (data->nodes[*j].is_builtin == 0)
        data->nodes[*j].is_valid_cmd = 0;
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
        data->nodes[j].is_valid_cmd = 1;
        if (data->nodes[j].cmd != NULL)
        {
            if (!is_executable(bin, data, &valid, &j) && !is_path(data, &valid, &j))
            {
                data->nodes[j].args[0] = ft_strdup(data->nodes[j].cmd);
            }   
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
    int i;

    env = getenv("PATH");
    bin = ft_split(env, ':');

    is_accessible(bin, data);
    i = -1;
    
    while (++i < data->pipe_count + 1)
    {
        if (data->nodes[i].is_valid_cmd == 0)
        {
            printf("%s : command not found\n", data->nodes[i].cmd);
            globals->status = 127;
            break;
        }
    }
    free_array((void **)bin);
    return (0);
}