#include "minishell.h"

t_export	*create_export_node(const char *key, const char *value)
{
	t_export *node;

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
	t_export    *current;

	current = head;
	while (current != NULL)
	{
		if (strcmp(current->key, key) == 0)
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

	klen = strlen(key);
	vlen = strlen(value);
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

t_export	*load_export(char *envp[])
{
	t_export	*head;
	char	    *key;
	char	    *value;
	char	    **str;
	int		        i;

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
	char	**rt;
	int		size;
	int		i;
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

void	update_export_node(t_export *head, const char *key, const char *new_value)
{
	t_export	*current;

	current = head;
	while (current != NULL)
	{
		if (strcmp(current->key, key) == 0)
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
		if (strcmp(current->key, key) == 0)
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