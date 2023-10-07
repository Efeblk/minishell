/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alakin <alakin@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 01:50:40 by alakin            #+#    #+#             */
/*   Updated: 2023/10/07 04:09:26 by alakin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	last_controller(t_data *data, t_token **tokens, t_index *index)
{
	data->nodes[index->node_index].args[index->arg_index] = NULL;
	data->nodes[index->node_index].operators[index->current_index] = NULL;
	free_tokens(tokens);
}
void	control_word(t_data *data, t_token **tokens, t_index *index)
{
	data->nodes[(*index).node_index].is_pipe = 0;
	if (tokens[0]->type != TOKEN_WORD)
		data->nodes[(*index).node_index].cmd = NULL;
}

int	fill_nodes(t_data *data, t_token **tokens, char *input, t_index *index)
{
	fill_index(index);
	fill_structs(data, tokens, input);
	while (tokens[(*index).i]->type != TOKEN_EOF)
	{
		control_word(data, tokens, index);
		if (tokens[(*index).i]->type == TOKEN_WORD)
			fill_cmd(data, tokens, index);
		else if ((tokens[(*index).i]->type == TOKEN_I
				|| tokens[(*index).i]->type == TOKEN_I_I))
		{
			if (!fill_infile(data, tokens, index))
				return (0);
		}
		else if ((tokens[(*index).i]->type == TOKEN_O
				|| tokens[(*index).i]->type
				== TOKEN_O_O) && (tokens[(*index).i + 1]->type != TOKEN_EOF))
		{
			if (!fill_outfile(data, tokens, index))
				return (0);
		}
		else if (tokens[(*index).i]->type == TOKEN_PIPE)
			pipe_situation(data, index);
		(*index).i++;
	}
	last_controller(data, tokens, index);
	return (1);
}
