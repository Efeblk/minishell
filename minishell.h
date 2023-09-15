/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibalik <ibalik@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 15:18:23 by alakin            #+#    #+#             */
/*   Updated: 2023/09/15 18:50:59 by ibalik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

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

typedef struct s_data
{
    int     pipe_count;
    t_env   *env;
    t_node  *nodes;
    char    **tokens;
} t_data;

int     env_count(char **envp);
char    **env_list(char **envp, t_env *env);

char	**ft_split(const char *s, char c);

size_t	ft_strlen(const char *s);
char    *ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strdup(const char *s1);
char	*ft_strjoin(char const *s1, char const *s2);

int     find_env(t_data data);

void    free_array(char **array);

int    executor(t_data data);
#endif