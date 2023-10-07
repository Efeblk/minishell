/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibalik <ibalik@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 02:50:34 by ibalik            #+#    #+#             */
/*   Updated: 2023/10/07 02:51:44 by ibalik           ###   ########.fr       */
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

void	update_status(int status, t_env **env)
{
	char	*tmpchar;

	tmpchar = ft_itoa(status);
	update_env_node(*env, "?", tmpchar);
	free (tmpchar);
}