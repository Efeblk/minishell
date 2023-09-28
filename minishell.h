
#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <string.h>
# include <ctype.h>
# include <unistd.h>
# include <fcntl.h>

#define NUM 1

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
    int     std_in;
    int     is_pipe;
    char    **operators;
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
int     ft_readline(t_data *data);
char	*ft_strdup(const char *s1);
char	**ft_split(const char *s, char c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
size_t	ft_strlen(const char *s);
char	*ft_strchr(const char *s, int c);
t_token *get_next_token(char **input);
t_token	*generate_word_token(char **input);
t_token	*generate_pr_token(char **input);
char	*create_word(char **input, char *start);
t_token	*create_token(TokenType type, char **input, char *start);
void	*ft_memcpy(void *dst, const void *src, size_t n);
t_token **allocate_tokens(int size);
t_token **resize_tokens(t_token **tokens, int size);
t_token **tokenize_input(char *input, int *count);
void    print_and_free_tokens(t_token **tokens, int count);
int     pipe_counter(t_data *data, t_token **tokens);
void    first_token_controller(t_token **tokens);
void    token_controller(t_token **tokens);
void    free_tokens(t_token **tokens);
void    fill_nodes(t_data *data, t_token **tokens); 
void    print_node(t_data *data);
void    fill_operators(t_token **tokens, t_data *data);
void    print_operators(t_data *data);
int     outfile_counter(t_token **tokens);
int     infile_counter(t_token **tokens);
int     operator_counter(t_token **tokens);
int     arg_counter(t_token **tokens);

int	    ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strjoin(char const *s1, char const *s2);

int     find_env(t_data *data);

void    free_array(void **array);
void    data_free(t_data *data);

int     is_input(char *cmd);

int     executor(t_data *data);
void    router(t_data data, int i, int *left_pipe, int *right_pipe);

#endif

