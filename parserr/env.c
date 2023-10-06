/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alakin <alakin@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 19:36:51 by alakin            #+#    #+#             */
/*   Updated: 2023/10/06 19:48:58 by alakin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*create_env_node(const char *key, const char *value)
{
	t_env	*node;

	node = (t_env *) malloc(sizeof(t_env));
	node->key = ft_strdup(key);
	node->value = ft_strdup(value);
	node->next = NULL;
	return (node);
}

void	add_env_node(t_env **head, const char *key, const char *value)
{
	t_env	*new_node;

	new_node = create_env_node(key, value);
	if (*head == NULL)
	{
		*head = new_node;
		return ;
	}
	new_node->next = *head;
	*head = new_node;
}

t_env	*find_env_node(t_env *head, const char *key)
{
	t_env	*current;

	current = head;
	while (current != NULL)
	{
		if (strcmp(current->key, key) == 0)
			return (current);
		current = current->next;
	}
	return (NULL);
}

void	free_env_list(t_env *head)
{
	t_env	*current;
	t_env	*next;

	current = head;
	while (current != NULL)
	{
		next = current->next;
		free(current->key);
		free(current->value);
		free(current);
		current = next;
	}
}

char	*join_env(const char *key, const char *value)
{
	size_t	klen;
	size_t	vlen;
	size_t	result_length;
	char	*result;

	klen = ft_strlen(key);
	vlen = ft_strlen(value);
	result_length = klen + vlen + 2;
	result = (char *) malloc(result_length * sizeof(char));
	if (!result)
	{
		printf("Memory allocation failed\n");
		return (NULL);
	}
	ft_memcpy(result, key, klen);
	result[klen] = '=';
	ft_memcpy(result + klen + 1, value, vlen + 1);
	return (result);
}
