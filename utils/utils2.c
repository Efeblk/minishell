#include "minishell.h"

void free_array(void **array)
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

void data_free(t_data *data)
{
	free(data->nodes->cmd);
	free_array((void **)data->nodes->args);
	free_array((void **)data->nodes->outfile);
	free_array((void **)data->nodes->infile);
	free_array((void **)data->nodes->operators);
	free(data->nodes);
}