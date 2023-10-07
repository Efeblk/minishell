/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alakin <alakin@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 02:32:29 by alakin            #+#    #+#             */
/*   Updated: 2023/10/07 03:42:01 by alakin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_array(void **array)
{
    if (array)
	{
		int	i;

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


void data_free(t_data *data)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (i < (data->pipe_count + 1))
    {
        if (data->nodes[i].cmd != NULL)
        {
            free(data->nodes[i].cmd);
            data->nodes[i].cmd = NULL;
        }
        if (data->nodes[i].args != NULL)
        {
            while (data->nodes[i].args[j] != NULL)
            {
                free(data->nodes[i].args[j]);
                j++;
            }
            free(data->nodes[i].args);
            data->nodes[i].args = NULL;
            j = 0;
        }

        if (data->nodes[i].outfile != NULL)
        {
            while (data->nodes[i].outfile[j] != NULL)
            {
                free(data->nodes[i].outfile[j]);
                j++;
            }
            free(data->nodes[i].outfile);
            data->nodes[i].outfile = NULL;
            j = 0;
        }
        if (data->nodes[i].infile != NULL)
        {
            while (data->nodes[i].infile[j] != NULL)
            {
                free(data->nodes[i].infile[j]);
                j++;
            }
            free(data->nodes[i].infile);
            data->nodes[i].infile = NULL;
            j = 0;
        }
        if (data->nodes[i].operators != NULL)
        {
            while (data->nodes[i].operators[j] != NULL)
            {
                free(data->nodes[i].operators[j]);
                j++;
            }
            free(data->nodes[i].operators);
            data->nodes[i].operators = NULL;
            j = 0;
        }
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


