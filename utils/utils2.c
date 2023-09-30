#include "minishell.h"

void free_array(void **array) 
{
    if (array) {
        int i = 0;
        while (array[i] != NULL) {
            free(array[i]);
            array[i] = NULL; // Set the freed pointer to NULL to avoid double-free
            i++;
        }
        free(array);
    }
}

void free_node(t_node *node) {
    if (node == NULL) {
        return;
    }

    // Free individual fields of the t_node structure
    if (node->cmd) {
        free(node->cmd);
        node->cmd = NULL;
    }
    free_array((void **)node->args);
    free_array((void **)node->outfile);
    free_array((void **)node->infile);
    free_array((void **)node->operators);
}

void data_free(t_data *data) {
    if (data == NULL) {
        return;
    }

    // Free the nodes array
    if (data->nodes) {
        int i = 0;
        while (i < data->pipe_count + 1) {
            free_node(&data->nodes[i]);
            i++;
        }
        free(data->nodes);
        data->nodes = NULL;
    }

    // Free the env structure
    if (data->env) {
        free_array((void **)data->env->env_list);
        free(data->env);
        data->env = NULL;
    }
}
