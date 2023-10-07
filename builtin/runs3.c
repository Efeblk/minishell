/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runs3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alakin <alakin@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 07:47:30 by alakin            #+#    #+#             */
/*   Updated: 2023/10/07 07:47:36 by alakin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
