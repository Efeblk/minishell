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
	if (data)
	{
		if (data->nodes)
		{
			if (data->nodes->cmd)
				free(data->nodes->cmd);
			if (data->nodes->args)
				free_array((void **)data->nodes->args);
			if (data->nodes->outfile)
				free_array((void **)data->nodes->outfile);
			if (data->nodes->infile)
				free_array((void **)data->nodes->infile);
			if (data->nodes->operators)
				free_array((void **)data->nodes->operators);
			free(data->nodes);
		}
	}
}