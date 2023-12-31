/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_router.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibalik <ibalik@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 02:12:05 by ibalik            #+#    #+#             */
/*   Updated: 2023/10/07 06:57:57 by ibalik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int	outfiler(char **outfiles, char **operators, int *j)
{
	int	i;
	int	fd;

	i = -1;
	while (outfiles[++i] && (((ft_strncmp(operators[i], ">", 1)) == 0)
			|| ((ft_strncmp(operators[i], ">>", 2)) == 0)))
	{
		if ((ft_strncmp(operators[i], ">", 2)) == 0)
			fd = open(outfiles[i], O_WRONLY | O_CREAT | O_TRUNC, 0777);
		else if ((ft_strncmp(operators[i], ">>", 2)) == 0)
			fd = open(outfiles[i], O_WRONLY | O_CREAT | O_APPEND, 0777);
		(*j)++;
	}
	(*j)--;
	return (fd);
}

static void	here_doc(t_data *data, int i)
{
	char	*tmp;
	char	*buffer;

	tmp = data->nodes[i].infile[0];
	while (1)
	{
		buffer = readline(">");
		if (ft_strncmp(buffer, tmp, sizeof(buffer)) == 0)
			break ;
		free(buffer);
	}
}

void	op_rout_helper(t_data *data, int i)
{
	char	*pwd;

	pwd = return_pwd();
	pwd = ft_strjoin(pwd, "/");
	pwd = ft_strjoin(pwd, data->nodes[i].infile[0]);
	if ((access(pwd, F_OK)) == 0)
		dup2(open(data->nodes[i].infile[0], O_RDONLY, 0777),
			STDIN_FILENO);
	else
		data->nodes[i].args[1] = ft_strdup(data->nodes[i].infile[0]);
	free(pwd);
}

void	op_router(t_data *data, int i)
{
	int		j;

	j = -1;
	while (data->nodes[i].operators[++j] != NULL)
	{
		if (ft_strncmp(data->nodes[i].operators[j], ">", 2) == 0)
			dup2(outfiler(data->nodes[i].outfile,
					data->nodes[i].operators, &j), STDOUT_FILENO);
		else if (ft_strncmp(data->nodes[i].operators[j], ">>", 2) == 0)
			dup2(outfiler(data->nodes[i].outfile,
					data->nodes[i].operators, &j), STDOUT_FILENO);
		else if (ft_strncmp(data->nodes[i].operators[j], "<", 2) == 0)
		{
			op_rout_helper(data, i);
		}
		else if (ft_strncmp(data->nodes[i].operators[j], "<<", 2) == 0)
			here_doc(data, i);
	}
}
