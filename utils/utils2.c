#include "minishell.h"

void free_array(void **array) 
{
    if (array) {
        int i = 0;
        while (array[i] != NULL)
        {
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

void data_free(t_data *data) 
{
    int i = 0;
    int j = 0;
    while (i < (data->pipe_count + 1))
    {
        if (data->nodes[i].cmd != NULL)
        {
            free(data->nodes[i].cmd);
            data->nodes[i].cmd = NULL;
        }
        if (data->nodes[i].args != NULL)
        {
            while (data->nodes[i].args[j] != NULL)
            {
                free(data->nodes[i].args[j]);
                j++;
            }
            free(data->nodes[i].args);
            data->nodes[i].args = NULL;
            j = 0;
        }

        if (data->nodes[i].outfile != NULL)
        {
            while (data->nodes[i].outfile[j] != NULL)
            {
                free(data->nodes[i].outfile[j]);
                j++;
            }
            free(data->nodes[i].outfile);
            data->nodes[i].outfile = NULL;
            j = 0;
        }
        if (data->nodes[i].infile != NULL)
        {
            while (data->nodes[i].infile[j] != NULL)
            {
                free(data->nodes[i].infile[j]);
                j++;
            }
            free(data->nodes[i].infile);
            data->nodes[i].infile = NULL;
            j = 0;
        }
        if (data->nodes[i].operators != NULL)
        {
            while (data->nodes[i].operators[j] != NULL)
            {
                free(data->nodes[i].operators[j]);
                j++;
            }
            free(data->nodes[i].operators);
            data->nodes[i].operators = NULL;
            j = 0;
        }
        i++;
    }
    if (data->nodes != NULL)
        free(data->nodes);
    if (data != NULL)
        free(data);
}

