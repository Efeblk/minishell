/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alakin <alakin@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 05:41:03 by alakin            #+#    #+#             */
/*   Updated: 2023/10/07 09:15:47 by alakin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigquit_handler(int num)
{
	(void)num;
	if (g_back == 1)
	{
		write(1, "\033[2D", 4);
		write(1, "  ", 2);
		write(1, "\033[2D", 4);
		ioctl(0, TIOCSTI);
		g_back = 0;
	}
	g_back = 1;
}

void	sigint_handler(int sig)
{
	(void)sig;
	write(1, "\033[A", 3);
	ioctl(0, TIOCSTI, "\n");
}

int	main(int argc, char *argv[], char *envp[])
{
	t_env		*env;
	t_export	*exp_list;
	t_globals	globals;
	t_data		*data;
	t_index		index;

	g_back = 0;
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigquit_handler);
	env = load_environment(envp, argc, argv);
	globals.user = get_env_val("USER", env);
	exp_list = load_export(envp);
	while (1)
	{
		data = malloc(sizeof(t_data));
		if (ft_readline(data, &globals, &env, &index))
		{
			built_in(data, &env, &exp_list);
			executor(data, &env);
			data_free(data);
		}
	}
	free_env_list(env);
	free_export_list(exp_list);
	return (0);
}
