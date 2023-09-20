
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
    char    *cmd;

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
}t_data;



int     env_count(char **envp);
char    **env_list(char **envp, t_env *env);
char    **add_env_list(t_env *env, char *str);
char	*ft_strdup(const char *s1);
char	**ft_split(const char *s, char c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
size_t	ft_strlen(const char *s);
char	*ft_strchr(const char *s, int c);
void    ft_readline(t_data *data);
void    space_separator(char *input);
char   *quote_separator(char *str);
int     quote_counter(char *str);

#endif

