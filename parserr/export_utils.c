/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alakin <alakin@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 19:46:41 by alakin            #+#    #+#             */
/*   Updated: 2023/10/06 22:36:17 by alakin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_export	*load_export(char *envp[])
{
	t_export	*head;
	char		*key;
	char		*value;
	char		**str;
	int			i;

	head = NULL;
	i = 0;
	while (envp[i] != NULL)
	{
		str = ft_split(envp[i], '=');
		key = ft_strdup(str[0]);
		value = ft_strdup(str[1]);
		free_array((void **)str);
		add_export_node(&head, key, value);
		free(key);
		free(value);
		i++;
	}
	return (head);
}

char	*get_export_val(const char *key, t_export *exp_list)
{
	t_export	*current;

	current = find_export_node(exp_list, key);
	if (!current)
	{
		printf("EXPORT VALUE DOESNT EXIST FOR KEY: %s", key);
		return (NULL);
	}
	return (current->value);
}

char	**get_export_arr(t_export *head)
{
	char		**rt;
	int			size;
	int			i;
	t_export	*current;

	current = head;
	size = 0;
	i = 0;
	while (current != NULL)
	{
		size++;
		current = current->next;
	}
	rt = (char **)malloc(sizeof(char *) * (size + 1));
	current = head;
	while (current != NULL)
	{
		rt[i] = join_export(current->key, current->value);
		i++;
		current = current->next;
	}
	rt[i] = 0;
	return (rt);
}

void	update_export_node(t_export *head,
	const char *key, const char *new_value)
{
	t_export	*current;

	current = head;
	while (current != NULL)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			free(current->value);
			current->value = ft_strdup(new_value);
			return ;
		}
		current = current->next;
	}
}

void	delete_export_node(t_export **head, const char *key)
{
	t_export	*current;
	t_export	*prev;

	current = *head;
	prev = NULL;
	while (current != NULL)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			if (prev == NULL)
				*head = current->next;
			else
				prev->next = current->next;
			free(current->key);
			free(current->value);
			free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}
