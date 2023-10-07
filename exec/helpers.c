/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alakin <alakin@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 03:06:20 by ibalik            #+#    #+#             */
/*   Updated: 2023/10/07 05:51:20 by alakin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_status(int status, t_env **env)
{
	char	*tmpchar;

	tmpchar = ft_itoa(status);
	update_env_node(*env, "?", tmpchar);
	free (tmpchar);
}

int	find_heredoc(char **operators)
{
	int	i;

	i = 0;
	while (operators[i] != NULL)
	{
		if (ft_strncmp(operators[i], "<<", 2) == 0)
			return (1);
	}
	return (0);
}
