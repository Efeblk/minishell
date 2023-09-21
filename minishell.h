/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibalik <ibalik@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 15:18:23 by alakin            #+#    #+#             */
/*   Updated: 2023/09/21 17:07:19 by ibalik           ###   ########.fr       */
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

int	ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlen(const char *s);
char    *ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strdup(const char *s1);
char	*ft_strjoin(char const *s1, char const *s2);

int     find_env(t_data data);

void    free_array(void **array);
void close_pipes(int **pipes, int pipe_size);

int is_input(char *cmd);

int     executor(t_data data);
void    router(t_data data, int i, int *fd, int *fd2);

#endif