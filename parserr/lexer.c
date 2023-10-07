/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alakin <alakin@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 01:13:25 by alakin            #+#    #+#             */
/*   Updated: 2023/10/07 08:07:31 by alakin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*get_next_token(char **input, t_data *data)
{
	while (isspace(**input))
		(*input)++;
	if (**input == '\0')
		return (create_token(TOKEN_EOF, input, *input));
	if (**input == '<' || **input == '>' || **input == '|')
		return (generate_pr_token(input));
	return (generate_word_token(input, data));
}

t_token	*generate_word_token(char **input, t_data *data)
{
	char	*start;

	start = *input;
	data->sf = 0;
	data->df = 0;
	while (**input)
	{
		if (!(data->sf || data->df)
			&& (ft_strchr("<>|", **input) || isspace(**input)))
			break ;
		if (**input == '"' && !data->sf)
			data->df = !data->df;
		if (**input == '\'' && !data->df)
			data->sf = !data->sf;
		(*input)++;
	}
	if (data->sf != 0 || data->df != 0)
	{
		printf("Error: Unbalanced quotes\n");
		exit(1);
	}
	return (create_token(TOKEN_WORD, input, start));
}

t_token	*generate_pr_token(char **input)
{
	if (**input == '|')
		return (create_token(TOKEN_PIPE, input, ++(*input) - 1));
	if (**input == '<')
	{
		if (*++(*input) == '<')
			return (create_token(TOKEN_I_I, input, ++(*input) - 2));
		return (create_token(TOKEN_I, input, (*input) - 1));
	}
	if (**input == '>')
	{
		if (*++(*input) == '>')
			return (create_token(TOKEN_O_O, input, ++(*input) - 2));
		return (create_token(TOKEN_O, input, (*input) - 1));
	}
	return (NULL);
}

char	*create_word(char **input, char *start)
{
	size_t	len;
	char	*word;

	len = *input - start;
	word = (char *) malloc(len + 1);
	ft_strncpy(word, start, len);
	word[len] = '\0';
	return (word);
}

t_token	*create_token(t_tokentype type, char **input, char *start)
{
	t_token	*token;

	token = (t_token *) malloc(sizeof(t_token));
	token->type = type;
	token->value = create_word(input, start);
	return (token);
}
