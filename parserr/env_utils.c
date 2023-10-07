/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alakin <alakin@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 19:40:18 by alakin            #+#    #+#             */
/*   Updated: 2023/10/07 04:10:39 by alakin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*load_environment(char *envp[])
{
	t_env	*head;
	char	*key;
	char	*value;
	char	**str;
	int		i;

	head = NULL;
	i = 0;
	while (envp[i] != NULL)
	{
		str = ft_split(envp[i], '=');
		key = ft_strdup(str[0]);
		value = ft_strdup(str[1]);
		free_array((void **)str);
		add_env_node(&head, key, value);
		free(key);
		free(value);
		i++;
	}
	add_env_node(&head, "?", "0");
	return (head);
}

char	*get_env_val(const char *key, t_env *env_list)
{
	t_env	*current;

	current = find_env_node(env_list, key);
	if (!current)
	{
		printf("ENV VALUE DOESNT EXIST FOR KEY: %s\n", key);
		return (NULL);
	}
	return (current->value);
}

char	**get_env_arr(t_env *head)
{
	char	**rt;
	int		size;
	int		i;
	t_env	*current;

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
		rt[i] = join_env(current->key, current->value);
		i++;
		current = current->next;
	}
	rt[i] = 0;
	return (rt);
}

void	update_env_node(t_env *head, const char *key, const char *new_value)
{
	t_env	*current;

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

void	delete_env_node(t_env **head, const char *key)
{
	t_env	*current;
	t_env	*prev;

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
