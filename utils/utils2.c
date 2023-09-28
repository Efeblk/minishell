#include "minishell.h"

void free_array(void **array)
{
    if (array)
    {
        int i;

        i = 0;
        while (array[i] != NULL)
        {
            free(array[i]);
            i++;
        }
        free(array);
    }   
}

void data_free(t_data *data)
{
    int i;

    if (data)
    {
        if (data->nodes)
        {
            i = 0;
            while (i < data->pipe_count + 1)
            {
                if (data->nodes[i].cmd)
                    free(data->nodes[i].cmd);
                if (data->nodes[i].args)
                    free_array((void **)data->nodes[i].args);
                if (data->nodes[i].outfile)
                    free_array((void **)data->nodes[i].outfile);
                if (data->nodes[i].infile)
                    free_array((void **)data->nodes[i].infile);
                if (data->nodes[i].operators)
                    free_array((void **)data->nodes[i].operators);

                i++;
            }
            free(data->nodes);
        }

        // Free the env structure
        if (data->env)
        {
            if (data->env->env_list)
                free_array((void **)data->env->env_list);
            free(data->env);
        }
    }
}
