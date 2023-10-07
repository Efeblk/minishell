/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alakin <alakin@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 03:38:29 by alakin            #+#    #+#             */
/*   Updated: 2023/10/07 03:38:30 by alakin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd_free(t_data *data, int i)
{
	free(data->nodes[i].cmd);
	data->nodes[i].cmd = NULL;
}

void	args_free(t_data *data, int i, int j)
{
	while (data->nodes[i].args[j] != NULL)
	{
		free(data->nodes[i].args[j]);
		j++;
	}
	free(data->nodes[i].args);
	data->nodes[i].args = NULL;
	j = 0;
}

void	outfile_free(t_data *data, int i, int j)
{
	while (data->nodes[i].outfile[j] != NULL)
	{
		free(data->nodes[i].outfile[j]);
		j++;
	}
	free(data->nodes[i].outfile);
	data->nodes[i].outfile = NULL;
	j = 0;
}

void	infile_free(t_data *data, int i, int j)
{
	while (data->nodes[i].infile[j] != NULL)
	{
		free(data->nodes[i].infile[j]);
		j++;
	}
	free(data->nodes[i].infile);
	data->nodes[i].infile = NULL;
	j = 0;
}

void	operators_free(t_data *data, int i, int j)
{
	while (data->nodes[i].operators[j] != NULL)
	{
		free(data->nodes[i].operators[j]);
		j++;
	}
	free(data->nodes[i].operators);
	data->nodes[i].operators = NULL;
	j = 0;
}
