/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibalik <ibalik@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 15:18:23 by alakin            #+#    #+#             */
/*   Updated: 2023/09/15 14:05:39 by ibalik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdlib.h>
#include <stdio.h>

typedef struct s_env
{
    char   **env_list;
    int    env_count;
} t_env;

typedef struct s_node
{
    char    *cmd;
    char    **args;
    char    **outfile;
    char    **infile;
}t_node;

int     env_count(char **envp);
char    **env_list(char **envp, t_env *env);
char	*ft_strdup(const char *s1);
char	**ft_split(const char *s, char c);
#endif