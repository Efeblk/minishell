/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alakin <alakin@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 15:18:23 by alakin            #+#    #+#             */
/*   Updated: 2023/09/15 11:41:43 by alakin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

typedef struct s_env
{
    char   **env_list;
    int    env_count;
} t_env;

typedef struct s_node
{
    char    **args;
    char    **outfile;
    char    **infile;
<<<<<<< HEAD
    char    *path;
    int     pipe_count;
}t_node;

int     env_count(char **envp);
char    **env_list(char **envp, t_env *env);
char	*ft_strdup(const char *s1);
char	**ft_split(const char *s, char c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
size_t	ft_strlen(const char *s);
void    ft_readline(t_node *node);
int     pipe_count(char *input, t_node *node);
=======
}t_node;
>>>>>>> 194cc3201f20e9c56e175aee771412ef2ef9a06d

int     env_count(char **envp);
char    **env_list(char **envp, t_env *env);
char	*ft_strdup(const char *s1);
char	**ft_split(const char *s, char c);
#endif