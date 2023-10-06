/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alakin <alakin@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 19:51:12 by alakin            #+#    #+#             */
/*   Updated: 2023/10/07 00:49:12 by alakin           ###   ########.fr       */
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

void	fill_structs(t_data *data, t_token **tokens, char *input)
{
	int	i;

	i = 0;
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
		data->nodes[(*index).node_index].cmd = ft_strdup(tokens[(*index).i]->value);
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

void	null_free_nodes(t_data *data, t_token **tokens, t_index *index)
{
	data->nodes[(*index).node_index].args[(*index).arg_index] = NULL;
	data->nodes[(*index).node_index].operators[(*index).current_index] = NULL;
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
		else if ((tokens[(*index).i]->type == TOKEN_O || tokens[(*index).i]->type
				== TOKEN_O_O) && (tokens[(*index).i + 1]->type != TOKEN_EOF))
		{
			if (!fill_outfile(data, tokens, index))
				return (0);
		}
		else if (tokens[(*index).i]->type == TOKEN_PIPE)
			pipe_situation(data, index);
		(*index).i++;
	}
	return (1);
}



// void print_node(t_data *data) 
// {
//     (void)data;
//         printf("CMD 1: %s\n", data->nodes[0].cmd);
//         printf("NODE[0].ARGS[1]: %s\n", data->nodes[0].args[1]);
//         printf("NODE[0].ARGS[2]: %s\n", data->nodes[0].args[2]);
//         printf("NODE[0].ARGS[3]: %s\n", data->nodes[0].args[3]);
//         //printf("OUTFILE:%s\n", data->nodes[0].outfile[0]);
//         //printf("CMD 2:%s\n", data->nodes[1].cmd);
//         //printf("OUTFILE[0]:%s\n", data->nodes[1].outfile[0]);
//         //printf("OUTFILE[1]:%s\n", data->nodes[1].outfile[1]);
//         //printf("OUTFILE[1]:%s\n", data->nodes[1].outfile[2]);
//         //printf("NODE[1].ARGS[1]:%s\n", data->nodes[1].args[1]);
//         //printf("NODE[1].ARGS[2]:%s\n", data->nodes[1].args[2]);
//         //printf("NODE[1].ARGS[3]:%s\n", data->nodes[1].args[3]);
//         //printf("NODE[1].INFILE:%s\n", data->nodes[1].infile[0]);
//         //printf("NODE[1].ARGS[1]: %s\n", data->nodes[1].args[1]);
//         //printf("NODE[1].OUTFILE %s\n", data->nodes[1].outfile[0]);
//         //printf("CMD 3: %s\n", data->nodes[2].cmd);
//         //printf("NODE[2].ARGS[1]: %s\n", data->nodes[2].args[1]);
//         //printf("NODE[2].ARGS[2]: %s\n", data->nodes[2].args[2]);
//         //printf("NODE[2].OUTFILE: %s\n", data->nodes[2].outfile[0]);
//         //printf("NODE[2].OUTFILE: %s\n", data->nodes[2].outfile[1]);
//         //printf("NODE[2].OUTFILE: %s\n", data->nodes[2].outfile[2]);
// }

/*void    fill_operators(t_token **tokens, t_data *data)
{
    (void)tokens;
    (void)data;
    return ;
}*/

/*void print_operators(t_data *data)
{
    (void)data;
    return ;
}*/