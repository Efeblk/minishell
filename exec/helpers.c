/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibalik <ibalik@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 03:06:20 by ibalik            #+#    #+#             */
/*   Updated: 2023/10/07 07:09:19 by ibalik           ###   ########.fr       */
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

	i = -1;
	while (operators[++i] != NULL)
	{
		if (ft_strncmp(operators[i], "<<", 2) == 0)
			return (1);
	}
	return (0);
}
