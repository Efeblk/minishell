/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibalik <ibalik@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 02:22:55 by ibalik            #+#    #+#             */
/*   Updated: 2023/10/07 05:02:02 by ibalik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_executable(char **bin, t_data *data, int *valid, int *j)
{
	int		i;
	char	*tmp;

	i = -1;
	while (bin[++i])
	{
		if (bin[i][ft_strlen(bin[i]) - 1] != '/')
			bin[i][ft_strlen(bin[i])] = '/';
		tmp = ft_strjoin(bin[i], data->nodes[*j].cmd); 
		if ((access(tmp, F_OK | X_OK)) == 0)
		{
			data->nodes[*j].args[0] = ft_strdup(tmp);
			*valid += 1;
			free(tmp);
			return (1);
		}
		free(tmp);
	}
	data->nodes[*j].is_valid_cmd = 0;
	return (0);
}

static int	is_path(t_data *data, int *valid, int *j)
{
	char	*c;
	char	*tmp;

	if (data->nodes[*j].cmd != NULL && data->nodes[*j].cmd[0] == '/')
	{
		data->nodes[*j].is_valid_cmd = 1;
		data->nodes[*j].args[0] = ft_strdup(data->nodes[*j].cmd);
		*valid += 1;
		return (1);
	}
	else if (data->nodes[*j].cmd[0] == '.' && data->nodes[*j].cmd[1] == '/')
	{
		data->nodes[*j].is_valid_cmd = 1;
		c = return_pwd();
		tmp = ft_strjoin(c, ++(data->nodes[*j].cmd));
		if ((access(tmp, F_OK | X_OK)) == -1)
			data->nodes[*j].is_valid_path = 0;
		data->nodes[*j].args[0] = tmp;
		--(data->nodes[*j].cmd);
		free(c);
		*valid += 1;
		return (1);
	}
	data->nodes[*j].is_valid_cmd = 0;
	return (0);
}

static int	is_accessible(char **bin, t_data *data)
{
	int	j;
	int	valid;

	valid = 0;
	j = -1;
	while (++j < (data->pipe_count + 1))
	{
		data->nodes[j].is_valid_path = 1;
		data->nodes[j].is_valid_cmd = 1;
		if (data->nodes[j].cmd != NULL)
		{
			if (data->nodes[j].is_builtin == 1
				&& ft_strncmp(data->nodes[j].cmd, "echo", 4))
			{
			}
			else if (!is_executable(bin, data, &valid, &j) &&
				!is_path(data, &valid, &j))
			{
				data->nodes[j].args[0] = ft_strdup(data->nodes[j].cmd);
			}
		}
		else if (data->nodes[j].cmd == NULL)
			valid += 1;
	}
	return (valid);
}

void	find_helper(t_data *data, t_env **env)
{
	int		i;

	i = -1;
	while (++i < data->pipe_count + 1)
	{
		if (data->nodes[i].cmd != NULL
			&& (data->nodes[i].is_valid_cmd == 0
				|| ft_strncmp(data->nodes[i].cmd, "$?", 2) == 0)
		)
		{
			printf("%s : command not found\n", data->nodes[i].cmd);
			update_status(127, env);
			break ;
		}
		else if (data->nodes[i].is_valid_path == 0)
		{
			printf("%s : not a valid path \n", data->nodes[i].cmd);
			update_status(127, env);
			break ;
		}
	}
}

int	find_env(t_data *data, t_env **env)
{
	char	*path;
	char	**bin;
	int		i;

	i = -1;
	path = get_env_val("PATH", *env);
	if (!path)
	{
		while (++i < data->pipe_count + 1)
		{
			if (data->nodes[i].is_valid_cmd == 0)
			{
				data->nodes[i].args[0] = ft_strdup(data->nodes[i].cmd);
			}
		}
		return (-1);
	}
	bin = ft_split(path, ':');
	is_accessible(bin, data);
	find_helper(data, env);
	free_array((void **)bin);
	return (0);
}