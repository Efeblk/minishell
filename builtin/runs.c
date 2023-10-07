/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibalik <ibalik@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 02:27:33 by ibalik            #+#    #+#             */
/*   Updated: 2023/10/07 03:14:44 by ibalik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	run_cd(t_data *data, int i)
{
	if (data->nodes[i].args[1])
		chdir(data->nodes[i].args[1]);
	else
		chdir(getenv("HOME"));
}

char	*return_pwd(void)
{
	return (getcwd(NULL, 0));
}

void	run_pwd(void)
{
	char	*s;

	s = getcwd(NULL, 0);
	if (!s)
	{
		perror("tsh: pwd getcwd error");
		exit(1);
	}
	else
		printf("%s\n", s);
	free(s);
}

void	run_exit(t_data *data, t_env **env, int i)
{
	int	tmp;

	if (data->nodes[i].args[1])
	{
		tmp = atoi(data->nodes[i].args[1]);
		update_status(tmp, env);
		printf("exit \n");
		data_free(data);
		exit(tmp);
	}
	data_free(data);
	printf("exit \n");
	exit(0);
}

void	run_echo(t_data *data, int i)
{
	int	j;

	j = 1;
	while (data->nodes[i].args[j] != NULL)
		j++;
	j--;
	if (data->nodes[i].args[j])
	{
		if (data->nodes[i].args[1][0] == '-'
			&& data->nodes[i].args[1][1] == 'n')
		{
			if (data->nodes[i].args[j][0] == '-'
				&& data->nodes[i].args[j][1] == 'n'
					&& data->nodes[i].args[j][2] == '\0')
			{
			}
			else
				printf("%s", data->nodes[i].args[j]);
		}
		else
			data->nodes[i].is_builtin = 0;
	}
}
