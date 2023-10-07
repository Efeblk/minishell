/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_start.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibalik <ibalik@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 02:26:27 by ibalik            #+#    #+#             */
/*   Updated: 2023/10/07 04:26:10 by ibalik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	helper_builtin(t_data *data, t_env **env, t_export **exp, int i)
{
	if (ft_strncmp(data->nodes[i].cmd, "clear", 5) == 0)
		printf("\033[2J\033[H");
	else if (ft_strncmp(data->nodes[i].cmd, "exit", 4) == 0)
		run_exit(data, env, i);
	else if (ft_strncmp(data->nodes[i].cmd, "pwd", 3) == 0)
		run_pwd();
	else if (ft_strncmp(data->nodes[i].cmd, "cd", 2) == 0)
		run_cd(data, i);
	else if (ft_strncmp(data->nodes[i].cmd, "echo", 4) == 0)
		run_echo(data, i);
	else if (ft_strncmp(data->nodes[i].cmd, "env", 3) == 0)
		run_env(*env);
	else if (ft_strncmp(data->nodes[i].cmd, "export", 6) == 0)
		run_export(exp, i, data, env);
	else if (ft_strncmp(data->nodes[i].cmd, "unset", 5) == 0)
		run_unset(env, exp, i, data);
	else
		data->nodes[i].is_builtin = 0;
}

static void	is_builtin(t_data *data, int i, t_env **env, t_export **exp_list)
{
	int	flag;

	data->nodes[i].is_builtin = 1;
	flag = question_mark(data, env);
	if (data->nodes[i].cmd != NULL)
	{
		if (flag == 0)
		{
			helper_builtin(data, env, exp_list, i);
		}
	}
	else
		data->nodes[i].is_builtin = 0;
}

void	built_in(t_data *data, t_env **env, t_export **exp_list)
{
	int	i;

	i = -1;
	while (++i < data->pipe_count + 1)
	{
		is_builtin(data, i, env, exp_list);
		if (data->nodes[i].is_builtin == 1)
			update_status(0, env);
	}
}
