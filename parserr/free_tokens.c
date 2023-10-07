/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alakin <alakin@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 19:48:41 by alakin            #+#    #+#             */
/*   Updated: 2023/10/07 04:30:51 by alakin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tokens(t_token **tokens)
{
	int	i;

	i = 0;
	while (tokens[i]->type != TOKEN_EOF)
	{
		free(tokens[i]->value);
		free(tokens[i]);
		i++;
	}
	free(tokens[i]->value);
	free(tokens[i]);
	free(tokens);
}

void	print_list(t_env *head)
{
	t_env	*current;

	current = head;
	while (current != NULL)
	{
		printf("%s=%s\n", current->key, current->value);
		current = current->next;
	}
}

void	print_export_list(t_export *head)
{
	t_export	*current;

	current = head;
	while (current != NULL)
	{
		if (current->value == NULL)
			printf("declare -x %s\n", current->key);
		else
			printf("declare -x %s=%s\n", current->key, current->value);
		current = current->next;
	}
}
