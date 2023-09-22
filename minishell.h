
#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <string.h>
 #include <ctype.h>

typedef enum
{
	TOKEN_PIPE,
	TOKEN_I,
	TOKEN_O,
	TOKEN_I_I,
	TOKEN_O_O,
	TOKEN_WORD,
	TOKEN_EOF
}				TokenType;

typedef struct s_token
{
    TokenType type;
    char      *value;
} t_token;

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
t_token *get_next_token(const char **input);
t_token	*generate_word_token(const char **input);
t_token	*generate_pr_token(const char **input);
char	*create_word(const char **input, const char *start);
t_token	*create_token(TokenType type, const char **input, const char *start);
void    *ft_realloc(void *ptr, size_t old_len, size_t new_len);
t_token **allocate_tokens(int size);
t_token **resize_tokens(t_token **tokens, int size);
t_token **tokenize_input(const char *input, int *count);
void print_and_free_tokens(t_token **tokens, int count);
#endif

