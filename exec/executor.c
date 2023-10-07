/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibalik <ibalik@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 02:18:30 by ibalik            #+#    #+#             */
/*   Updated: 2023/10/07 03:12:07 by ibalik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	first_process(t_data *data, int **pipes, int i)
{
	if (data->pipe_count > 0)
	{
		dup2(pipes[0][1], STDOUT_FILENO);
	}
	close_pipes(pipes, data->pipe_count);
	op_router(data, i);
}

static void	middle_process(t_data *data, int **pipes, int i)
{
	if (find_heredoc(data->nodes[i].operators) == 0)
	{
		dup2(pipes[i - 1][0], STDIN_FILENO);
		dup2(pipes[i][1], STDOUT_FILENO);
	}
	close_pipes(pipes, data->pipe_count);
	op_router(data, i);
}

static void	last_process(t_data *data, int **pipes, int i)
{
	if (find_heredoc(data->nodes[i].operators) == 0)
	{
		dup2(pipes[i - 1][0], STDIN_FILENO);
	}
	close_pipes(pipes, data->pipe_count);
	op_router(data, i);
}

static void	process_router(int i, t_data *data, int **pipes, t_env **env)
{
	char	**envs;

	if (i == 0)
		first_process(data, pipes, i);
	else if (i == data->pipe_count)
		last_process(data, pipes, i);
	else
		middle_process(data, pipes, i);
	if (data->nodes[i].is_valid_path == 1)
	{
		envs = get_env_arr(*env);
		execve(data->nodes[i].args[0], data->nodes[i].args, envs);
	}
}

int	executor(t_data *data, t_env **env)
{
	int		**pipes;
	pid_t	*pids;
	int		i;

	find_env(data, env);
	i = -1;
	pipes = pipe_create(data->pipe_count);
	pids = pid_create(data->pipe_count + 1);
	while (++i < (data->pipe_count + 1))
	{
		if (data->nodes[i].is_builtin == 0
			&& data->nodes[i].is_valid_cmd == 1
			&& data->nodes[i].is_valid_path == 1
		)
		{
			pids[i] = fork();
			if (pids[i] == 0)
			{
				process_router(i, data, pipes, env);
				exit(0);
			}
		}
	}
	wait_close_free(data, pipes, pids, env);
	return (0);
}
