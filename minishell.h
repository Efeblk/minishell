
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
    char    **args;
    char    **outfile;
    char    **infile;
    int     arg_count;
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
char    **add_env_list(t_env *env, char *str);
char	*ft_strdup(const char *s1);
char	**ft_split(const char *s, char c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
size_t	ft_strlen(const char *s);
void    ft_readline(t_data *data);
int     arg_count(t_data *data);
#endif

