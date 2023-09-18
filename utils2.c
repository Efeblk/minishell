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

void close_pipes(int **pipes, int pipe_size)
{
	int i;

	i = -1;
	while (++i < pipe_size)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
	}
	free_array((void **)pipes);
}
