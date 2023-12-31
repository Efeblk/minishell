/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alakin <alakin@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 05:35:33 by alakin            #+#    #+#             */
/*   Updated: 2023/10/07 08:59:44 by alakin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_expanded(const char *str, t_env **env_list, t_data *data)
{
	t_exp_stsh	*stsh;
	char		*rt;

	stsh = get_stsh(str);
	data->sf = 0;
	data->df = 0;
	expand_stsh(str, stsh, data, env_list);
	free((char *)str);
	rt = stsh->rt;
	free(stsh);
	return (rt);
}

void	expand_stsh(const char *str, t_exp_stsh *stsh,
	t_data *data, t_env **env_list)
{
	while (str[stsh->src_i])
	{
		if (str[stsh->src_i] == '"' && !data->sf)
			data->df = !data->df;
		else if (str[stsh->src_i] == '\'' && !data->df)
			data->sf = !data->sf;
		else if (str[stsh->src_i] == '$' && !data->sf)
			ft_dollarize(str, stsh, env_list);
		else
		{
			stsh->rt[stsh->rt_i++] = str[stsh->src_i];
		}
		stsh->src_i++;
	}
	stsh->rt[stsh->rt_i] = '\0';
}

void	dollar_helper(t_exp_stsh *stsh, char *var_val, int var_len)
{
	stsh->rt_len += ft_strlen(var_val) - (1 + var_len);
	stsh->rt = (char *)ft_realloc(stsh->rt, stsh->rt_len, sizeof(char));
	ft_strcpy(stsh->rt + stsh->rt_i, var_val);
	stsh->rt_i += ft_strlen(var_val);
}

void	ft_dollarize(const char *str, t_exp_stsh *stsh, t_env **env_list)
{
	int		var_start;
	int		var_len;
	char	*var_name;
	char	*var_val;

	var_start = stsh->src_i + 1;
	var_len = 0;
	while (str[var_start + var_len] != '\0'
		&& (ft_isalnum(str[var_start + var_len])
			|| str[var_start + var_len] == '_'))
		var_len++;
	var_name = (char *)malloc(var_len + 1);
	ft_strncpy(var_name, str + var_start, var_len);
	var_name[var_len] = '\0';
	if (ft_strcmp(var_name, "") == 0)
		var_val = get_env_val("?", *env_list);
	else
		var_val = get_env_val(var_name, *env_list);
	free(var_name);
	if (var_val)
		dollar_helper(stsh, var_val, var_len);
	stsh->src_i += var_len;
}

t_exp_stsh	*get_stsh(const char *str)
{
	t_exp_stsh	*rt;

	rt = (t_exp_stsh *)malloc(sizeof(t_exp_stsh));
	rt->rt_i = 0;
	rt->src_i = 0;
	rt->src_len = ft_strlen(str);
	rt->rt_len = rt->src_len;
	rt->rt = (char *)malloc(sizeof(char) * (rt->rt_len + 1));
	return (rt);
}
