/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alakin <alakin@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 19:51:12 by alakin            #+#    #+#             */
/*   Updated: 2023/10/07 01:52:02 by alakin           ###   ########.fr       */
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



void	null_free_nodes(t_data *data, t_token **tokens, t_index *index)
{
	data->nodes[(*index).node_index].args[(*index).arg_index] = NULL;
	data->nodes[(*index).node_index].operators[(*index).current_index] = NULL;
	free_tokens(tokens);
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