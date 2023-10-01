#include "minishell.h"

void free_array(void **array) 
{
    if (array) {
        int i = 0;
        while (array[i] != NULL)
        {
            printf("array:    %i   \n", i);
            free(array[i]);
            array[i] = NULL; // Set the freed pointer to NULL to avoid double-free
            i++;
        }
        //free(array[i]);
        free(array);
    }
}

void free_node(t_node *node)
 {
    if (node == NULL) {
        return;
    }
    printf("node 1\n");
    // Free individual fields of the t_node structure
    if (node->cmd) {
        free(node->cmd);
        node->cmd = NULL;
    }

    printf("node 2\n");
    free_array((void **)node->args);
    printf("node 3\n");
    free_array((void **)node->outfile);
    printf("node 4\n");
    free_array((void **)node->infile);
    printf("node 5\n");
    free_array((void **)node->operators);
    printf("node 6\n");
}

void data_free(t_data *data) {
    if (data == NULL) {
        return;
    }

    int i = 0;
    while (i < data->pipe_count + 1) 
    {
        printf("trying to free \n");
        free_node(&data->nodes[i]);
        i++;
    }
    printf("ENV \n");
    // if (data->env) {
    //     free_array((void **)data->env->env_list);
    //     free(data->env);
    //     data->env = NULL;
    // }
}
