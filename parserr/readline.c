/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alakin <alakin@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 05:27:22 by alakin            #+#    #+#             */
/*   Updated: 2023/10/07 05:28:14 by alakin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	controller(t_token **tokens, int i)
{
	if (!pipe_controller_printer(tokens, i))
		return (0);
	else if (tokens[i + 1]->type == TOKEN_I)
	{
		printf("syntax error near unexpected token '<'\n");
		return (0);
	}
	else if (tokens[i + 1]->type == TOKEN_O)
	{
		printf("syntax error near unexpected token '>'\n");
		return (0);
	}
	else if (tokens[i + 1]->type == TOKEN_O_O)
	{
		printf("syntax error near unexpected token '>>'\n");
		return (0);
	}
	return (1);
}

int	token_controller_2(t_token **tokens, int i)
{
	if (tokens[i]->type == TOKEN_PIPE)
	{
		if (!controller(tokens, i))
			return (0);
	}
	else if (tokens[i]->type == TOKEN_I)
	{
		if (!controller(tokens, i))
			return (0);
	}
	else if (tokens[i]->type == TOKEN_I_I)
	{
		if (!controller(tokens, i))
			return (0);
	}
	return (1);
}

int	token_controller(t_token **tokens)
{
	int	i;

	i = -1;
	while (tokens[++i]->type != TOKEN_EOF)
	{
		if (!token_controller_2(tokens, i))
			return (0);
		else if (tokens[i]->type == TOKEN_O)
		{
			if (!controller(tokens, i))
				return (0);
		}
		else if (tokens[i]->type == TOKEN_O_O)
		{
			if (!controller(tokens, i))
				return (0);
		}
	}
	return (1);
}

int	main_controller(t_data *data, t_token **tokens, char *input, char *print)
{
	if (!first_token_controller(tokens))
	{
		free_main(tokens, input, data, print);
		return (0);
	}
	if (!token_controller(tokens))
	{
		free_main(tokens, input, data, print);
		return (0);
	}
	return (1);
}

int	ft_readline(t_data *data, t_globals *globals,
	t_env **env_list, t_index *index)
{
	char	*input;
	t_token	**tokens;
	char	*print;

	print = full_pwd(globals);
	input = readline(print);
	add_history(input);
	if (!input_check(input, print, data))
		return (0);
	input = get_expanded(input, env_list);
	tokens = tokenize_input(input);
	if (!main_controller(data, tokens, input, print))
		return (0);
	data->pipe_count = pipe_counter(data, tokens);
	if (!fill_nodes(data, tokens, input, index))
	{
		free_main2(tokens, input, data, print);
		return (0);
	}
	free(input);
	free(print);
	print = NULL;
	return (1);
}
