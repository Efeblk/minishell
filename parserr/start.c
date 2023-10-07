/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alakin <alakin@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 19:57:40 by alakin            #+#    #+#             */
/*   Updated: 2023/10/07 05:35:09 by alakin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	**allocate_tokens(int size)
{
	t_token	**tokens;

	tokens = malloc(sizeof(t_token *) * size);
	if (tokens == NULL)
	{
		printf("Memory allocation failed\n");
		exit(1);
	}
	return (tokens);
}

int	count_tokens(char *input)
{
	int		count;
	t_token	*token;

	count = 0;
	while (1)
	{
		token = get_next_token(&input);
		count++;
		if (token->type == TOKEN_EOF)
		{
			free(token->value);
			free(token);
			break ;
		}
		free(token->value);
		free(token);
	}
	return (count);
}

t_token	**tokenize_input(char *input)
{
	int			size;
	t_token		**tokens;
	t_token		*token;
	int			i;

	i = 0;
	size = count_tokens(input);
	tokens = allocate_tokens(size);
	while (1)
	{
		token = get_next_token(&input);
		tokens[i] = malloc(sizeof(t_token));
		tokens[i]->type = token->type;
		tokens[i]->value = ft_strdup(token->value);
		i++;
		if (token->type == TOKEN_EOF)
		{
			free(token->value);
			free(token);
			break ;
		}
		free(token->value);
		free(token);
	}
	return (tokens);
}

int	first_token_controller(t_token **tokens)
{
	if (tokens[0]->type == TOKEN_PIPE)
	{
		printf("syntax error near unexpected token `|'\n");
		return (0);
	}
	else if ((tokens[0]->type == TOKEN_I || tokens[0]->type == TOKEN_I_I
			|| tokens[0]->type == TOKEN_O
			|| tokens[0]->type == TOKEN_O_O)
		&& tokens[1]->type == TOKEN_EOF)
	{
		printf("syntax error near unexpected token `newline' \n");
		return (0);
	}
	else
		return (1);
}

int	pipe_controller_printer(t_token **tokens, int i)
{
	if (tokens[i + 1]->type == TOKEN_PIPE)
	{
		printf("syntax error near unexpected token `|'\n");
		return (0);
	}
	return (1);
}
