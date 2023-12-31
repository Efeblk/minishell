/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibalik <ibalik@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 02:32:29 by alakin            #+#    #+#             */
/*   Updated: 2023/10/07 06:55:10 by ibalik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_array(void **array)
{
	int	i;

	if (array)
	{
		i = 0;
		while (array[i] != NULL)
		{
			free(array[i]);
			array[i] = NULL;
			i++;
		}
		free(array);
	}
}

void	data_free(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < (data->pipe_count + 1))
	{
		if (data->nodes[i].cmd != NULL)
			cmd_free(data, i);
		if (data->nodes[i].args != NULL)
			args_free(data, i, j);
		if (data->nodes[i].outfile != NULL)
			outfile_free(data, i, j);
		if (data->nodes[i].infile != NULL)
			infile_free(data, i, j);
		if (data->nodes[i].operators != NULL)
			operators_free(data, i, j);
		i++;
	}
	if (data->nodes != NULL)
		free(data->nodes);
	if (data != NULL)
		free(data);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 == *s2 && *s1)
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

int	ft_isalnum(int c)
{
	return (ft_isdigit(c) || ft_isalpha(c));
}

void	*ft_realloc(void *ptr, size_t b_amount, size_t b_size)
{
	void	*rt;
	int		msize;

	msize = b_amount * b_size;
	rt = malloc((b_amount + 1) * b_size);
	rt = ft_memcpy(rt, ptr, msize);
	free(ptr);
	return (rt);
}
