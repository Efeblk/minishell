#include "minishell.h"

t_node	*create_env_node(const char *key, const char *value)
{
	t_env *node;

	node = (t_node *) malloc(sizeof(t_node));
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

t_node	*find_env_node(t_env *head, const char *key)
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

	klen = strlen(key);
	vlen = strlen(value);
	result_length = klen + vlen + 2;
	result = (char *)malloc(result_length * sizeof(char));
	if (!result)
	{
		printf("Memory allocation failed\n");
		return (NULL);
	}
	memcpy(result, key, klen);
	result[klen] = '=';
	memcpy(result + klen + 1, value, vlen + 1);
	return (result);
}

t_env	*load_environment(char *envp[])
{
	t_env	*head;
	char	*key;
	char	*value;
	char	*full;
	int		i;

	head = NULL;
	i = 0;
	while (envp[i] != NULL)
	{
		key = strtok(envp[i], "=");
		value = strtok(NULL, "=");
		full = envp[i];
		add_env_node(&head, key, value);
		i++;
	}
	return (head);
}

char	*get_env_val(const char *key)
{
	t_env	*current;

	current = find_env_node(env_list, key);
	if (!current)
	{
		printf("ENV VALUE DOESNT EXIST FOR KEY: %s", key);
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
		if (strcmp(current->key, key) == 0)
		{
			free(current->value);
			current->value = strdup(new_value);
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
		if (strcmp(current->key, key) == 0)
		{
			if (prev == NULL)
			{
				*head = current->next;
			}
			else
			{
				prev->next = current->next;
			}
			free(current->key);
			free(current->value);
			free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}

int main(int argc, char *argv[], char *envp[])
{
	t_env *env_list = load_environment(envp);

	printf("Original environment variables:\n");
	print_list(env_list);

	// Add a new variable
	add_env_node(&env_list, "NEW_VARIABLE", "new_value");
	printf("\nAfter adding NEW_VARIABLE:\n");
	print_list(env_list);

	// Update an existing variable
	update_env_node(env_list, "PATH", "/new/path");
	printf("\nAfter updating PATH:\n");
	print_list(env_list);

	// Delete a variable
	delete_env_node (&env_list, "NEW_VARIABLE");
	printf("\nAfter deleting NEW_VARIABLE:\n");
	print_list(env_list);

	free_list(env_list);
	return 0;
}