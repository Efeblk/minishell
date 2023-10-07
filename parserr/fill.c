/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alakin <alakin@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 01:33:11 by alakin            #+#    #+#             */
/*   Updated: 2023/10/07 02:41:24 by alakin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fill_index(t_index *index)
{
	(*index).i = 0;
	(*index).node_index = 0;
	(*index).arg_index = 0;
	(*index).y = 0;
	(*index).x = 0;
	(*index).current_index = 0;
}

void	fill_cmd(t_data *data, t_token **tokens, t_index *index)
{
	if ((*index).arg_index == 0)
	{
		data->nodes[(*index).node_index].cmd
			= ft_strdup(tokens[(*index).i]->value);
		(*index).arg_index++;
	}
	else
	{
		data->nodes[(*index).node_index].args[(*index).arg_index]
			= ft_strdup(tokens[(*index).i]->value);
		(*index).arg_index++;
	}
}

int	fill_infile(t_data *data, t_token **tokens, t_index *index)
{
	if (tokens[(*index).i + 1]->type == TOKEN_EOF)
	{
		printf("syntax error near unexpected token `newline\n'");
		return (0);
	}
	else
	{
		data->nodes[(*index).node_index].infile[(*index).x]
			= ft_strdup(tokens[(*index).i + 1]->value);
		data->nodes[(*index).node_index].operators[(*index).current_index]
			= ft_strdup(tokens[(*index).i]->value);
		(*index).current_index++;
		(*index).x++;
		(*index).i++;
	}
	return (1);
}

int	fill_outfile(t_data *data, t_token **tokens, t_index *index)
{
	if (tokens[(*index).i + 1]->type == TOKEN_EOF)
	{
		printf("syntax error near unexpected token `newline\n'");
		return (0);
	}
	else
	{
		data->nodes[(*index).node_index].outfile[(*index).y]
			= ft_strdup(tokens[(*index).i + 1]->value);
		data->nodes[(*index).node_index].operators[(*index).current_index]
			= ft_strdup(tokens[(*index).i]->value);
		(*index).current_index++;
		(*index).y++;
		(*index).i++;
	}
	return (1);
}

void	pipe_situation(t_data *data, t_index *index)
{
	data->nodes[(*index).node_index].is_pipe = 1;
	data->nodes[(*index).node_index].args[(*index).arg_index + 1] = NULL;
	data->nodes[(*index).node_index].infile[(*index).x] = NULL;
	data->nodes[(*index).node_index].outfile[(*index).y] = NULL;
	data->nodes[(*index).node_index].operators[(*index).current_index] = NULL;
	(*index).node_index++;
	data->nodes[(*index).node_index].cmd = NULL;
	(*index).arg_index = 0;
	(*index).current_index = 0;
	(*index).x = 0;
	(*index).y = 0;
}
