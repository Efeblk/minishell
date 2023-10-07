/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runs2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibalik <ibalik@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 02:30:40 by ibalik            #+#    #+#             */
/*   Updated: 2023/10/07 02:30:56 by ibalik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	run_env(t_env *env_list)
{
	print_list(env_list);
}

void	run_export(t_export **exp_list, int i, t_data *data, t_env **env)
{
	int	j;

	j = 0;
	if (data->nodes[i].args[1] == NULL)
		print_export_list(*exp_list);
	else
	{
		while (data->nodes[i].args[++j])
		{
			if ((ft_strchr(data->nodes[i].args[j], '=')))
			{
				add_export(i, data, exp_list, j);
				add_env(i, data, env, j);
			}
			else if (!(ft_strchr(data->nodes[i].args[j], '=')))
				add_export(i, data, exp_list, j);
		}
	}
}

void	add_export(int i, t_data *data, t_export **exp_list, int j)
{
	char	**str;
	char	*key;
	char	*value;

	if ((ft_strchr(data->nodes[i].args[j], '=')))
	{
		if (data->nodes[i].args[j][0] != '=')
		{
			str = ft_split(data->nodes[i].args[j], '=');
			key = ft_strdup(str[0]);
			value = ft_strdup(str[1]);
			free_array((void **)str);
			if (find_export_node(*exp_list, key))
			{
				if (value)
					update_export_node(*exp_list, key, value);
			}
			else
				add_export_node(exp_list, key, value);
			free(key);
			free(value);
		}
		else
			printf("export: '%s': not a valid identifier\n",
				data->nodes[i].args[j]);
	}
	else
	{
		if (!find_export_node(*exp_list, data->nodes[i].args[j]))
			add_export_node(exp_list, data->nodes[i].args[j], "");
	}
}

void 	add_env(int i, t_data *data, t_env **env_list, int j)
{
	char	**str;
	char	*key;
	char	*value;

	if (data->nodes[i].args[j][0] != '=')
	{
		str = ft_split(data->nodes[i].args[j], '=');
		key = ft_strdup(str[0]);
		value = ft_strdup(str[1]);
		free_array((void **)str);
		if (find_env_node(*env_list, key))
			update_env_node(*env_list, key, value);
		else
			add_env_node(env_list, key, value);
		free(key);
		free(value);
	}
}

void	run_unset(t_env **env, t_export **exp_list, int i, t_data *data)
{
	int	j;

	j = 0;
	while (data->nodes[i].args[++j])
	{
		if (find_env_node(*env, data->nodes[i].args[j]))
			delete_env_node(env, data->nodes[i].args[j]);
		if (find_export_node(*exp_list, data->nodes[i].args[j]))
			delete_export_node(exp_list, data->nodes[i].args[j]);
	}
}