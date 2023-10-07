/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alakin <alakin@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 19:51:12 by alakin            #+#    #+#             */
/*   Updated: 2023/10/07 04:36:30 by alakin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	outfile_counter(t_token **tokens)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (tokens[i]->type != TOKEN_EOF)
	{
		if (tokens[i]->type == TOKEN_O || tokens[i]->type == TOKEN_O_O)
			count++;
		i++;
	}
	return (count);
}

int	infile_counter(t_token **tokens)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (tokens[i]->type != TOKEN_EOF)
	{
		if (tokens[i]->type == TOKEN_I || tokens[i]->type == TOKEN_I_I)
			count++;
		i++;
	}
	return (count);
}

int	operator_counter(t_token **tokens)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (tokens[i]->type != TOKEN_EOF)
	{
		if (tokens[i]->type != TOKEN_WORD)
			count++;
		i++;
	}
	return (count);
}

void	fill_structs(t_data *data, t_token **tokens,
	char *input, t_index *index)
{
	int	i;

	i = 0;
	fill_index(index);
	data->nodes = malloc(sizeof(t_node) * (data->pipe_count + 1));
	while (i < (data->pipe_count + 1))
	{
		data->nodes[i].args = calloc(sizeof(input), sizeof(char *));
		data->nodes[i].outfile = calloc((outfile_counter(tokens) + 1),
				sizeof(char *));
		data->nodes[i].infile = calloc((infile_counter(tokens) + 1),
				sizeof(char *));
		data->nodes[i].operators = calloc((operator_counter(tokens) + 1),
				sizeof(char *));
		i++;
	}
}

void	null_free_nodes(t_data *data, t_token **tokens, t_index *index)
{
	data->nodes[(*index).node_index].args[(*index).arg_index] = NULL;
	data->nodes[(*index).node_index].operators[(*index).current_index] = NULL;
	free_tokens(tokens);
}
