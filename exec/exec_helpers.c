/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibalik <ibalik@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 02:50:34 by ibalik            #+#    #+#             */
/*   Updated: 2023/10/07 06:11:08 by ibalik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	**pipe_create(int pipe_count)
{
	int	i;
	int	**pipes;

	i = -1;
	if (pipe_count == 0)
	{
		pipes = (int **)malloc(sizeof(int *) * 2);
		pipes[0] = NULL;
		pipes[1] = NULL;
		return (pipes);
	}
	pipes = (int **)malloc(sizeof(int *) * (pipe_count + 1));
	while (++i < pipe_count)
	{
		pipes[i] = (int *)malloc(sizeof(int) * 2);
		if (pipe(pipes[i]) == -1)
		{
			perror("pipe");
			return (NULL);
		}
	}
	pipes[i] = NULL;
	return (pipes);
}

void	close_pipes(int **pipes, int pipe_count)
{
	int	i;

	i = 0;
	while (i < pipe_count)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		free(pipes[i]);
		i++;
	}
	free(pipes);
}

pid_t	*pid_create(int size)
{
	pid_t	*tmp;

	tmp = (pid_t *)malloc(sizeof(pid_t) * size);
	return (tmp);
}

void	wait_close_free(t_data *data, int **pipes, int *pids, t_env **env)
{
	int		i;
	char	*chart;
	int		status;

	chart = get_env_val("?", *env);
	status = atoi(chart);
	i = -1;
	close_pipes(pipes, data->pipe_count);
	while (++i < data->pipe_count + 1)
	{
		waitpid(pids[i], &status, 0);
		if (status < 255)
			status = status % 255;
		update_status(status, env);
	}
	free(pids);
}
