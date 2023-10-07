/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   question_mark.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibalik <ibalik@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 04:10:44 by ibalik            #+#    #+#             */
/*   Updated: 2023/10/07 06:56:14 by ibalik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	helper1(t_data *data, int *status, t_env **env, int i)
{
	if (data->nodes[i].cmd[0] == '$' && data->nodes[i].cmd[1] == '?')
	{
		if (*status > 255)
		{
			*status = *status % 255;
			update_status(*status, env);
		}
		printf("%i: ", *status);
		return (1);
	}
	return (0);
}

static int	helper2(t_data *data, int *status, t_env **env, int i)
{
	int	j;

	j = -1;
	while (data->nodes[i].args[++j] != NULL)
	{
		if (data->nodes[i].args[j][0] == '$'
			&& data->nodes[i].args[j][1] == '?')
		{
			if (*status > 255)
			{
				*status = *status % 255;
				update_status(*status, env);
			}
			printf("%i: ", *status);
			return (1);
		}
	}
	return (0);
}

int	question_mark(t_data *data, t_env **env)
{
	int		i;
	int		j;
	int		status;
	char	*tmp;

	j = -1;
	i = -1;
	tmp = get_env_val("?", *env);
	status = ft_atoi(tmp);
	while (++i < data->pipe_count + 1)
	{
		if (data->nodes[i].cmd != NULL)
		{
			if (helper1(data, &status, env, i) == 1)
				return (1);
		}
		else
		{
			if (helper2(data, &status, env, i) == 1)
				return (1);
		}
	}
	return (0);
}
