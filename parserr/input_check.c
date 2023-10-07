/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alakin <alakin@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 05:16:12 by alakin            #+#    #+#             */
/*   Updated: 2023/10/07 05:36:12 by alakin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*full_pwd(t_globals *globals)
{
	char	*pwd;
	char	*suffix;
	char	*user;
	char	*print;
	char	*env;

	env = globals->user;
	pwd = return_pwd();
	suffix = ft_strjoin(pwd, ":>");
	user = ft_strjoin(env, "@");
	print = ft_strjoin(user, suffix);
	free(pwd);
	free(user);
	free(suffix);
	pwd = NULL;
	suffix = NULL;
	user = NULL;
	env = NULL;
	return (print);
}

int	input_check(char *input, char *print, t_data *data)
{
	if (input[0] == '\0')
	{
		free(print);
		print = NULL;
		free(data);
		free(input);
		return (0);
	}
	return (1);
}

void	free_main(t_token **tokens, char *input, t_data *data, char *print)
{
	free(print);
	print = NULL;
	free_tokens(tokens);
	free(input);
	free(data);
}

void	free_main2(t_token **tokens, char *input, t_data *data, char *print)
{
	free(print);
	free_tokens(tokens);
	free(input);
	data_free(data);
}
