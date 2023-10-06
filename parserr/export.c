/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alakin <alakin@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 22:35:47 by alakin            #+#    #+#             */
/*   Updated: 2023/10/06 22:36:28 by alakin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_export	*create_export_node(const char *key, const char *value)
{
	t_export	*node;

	node = (t_export *) malloc(sizeof(t_export));
	node->key = ft_strdup(key);
	if (value != NULL && value[0] != '\0')
		node->value = ft_strdup(value);
	else
		node->value = NULL;
	node->next = NULL;
	return (node);
}


void	add_export_node(t_export **head, const char *key, const char *value)
{
	t_export	*new_node;

	new_node = create_export_node(key, value);
	if (*head == NULL)
	{
		*head = new_node;
		return ;
	}
	new_node->next = *head;
	*head = new_node;
}

t_export	*find_export_node(t_export *head, const char *key)
{
	t_export	*current;

	current = head;
	while (current != NULL)
	{
		if (ft_strcmp(current->key, key) == 0)
			return (current);
		current = current->next;
	}
	return (NULL);
}

void	free_export_list(t_export *head)
{
	t_export	*current;
	t_export	*next;

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

char	*join_export(const char *key, const char *value)
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
