
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
    char    *key;
    char    *value;
    struct  s_env *next;
} t_env;

typedef struct s_export
{
    char    *key;
    char    *value;
    struct  s_export *next;
} t_export;

typedef struct s_node
{
    char    *cmd;
    char    **args;
    char    **outfile;
    char    **infile;
    int     is_pipe;
    char    **operators;
    int     arg_count;
    int     is_builtin;
    int     is_valid_cmd;
}t_node;


typedef struct s_data
{
    int     pipe_count;
    t_env   *env;
    t_node  *nodes;
    int     count;
}t_data;

typedef struct s_globals
{
    char *user;
    int status;
}t_globals;


int     ft_readline(t_data *data, t_globals *globals);
char    *ft_strdup(const char *s1);
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
t_token **tokenize_input(char *input);
int count_tokens(char *input);
void    print_and_free_tokens(t_token **tokens, int count);
int     pipe_counter(t_data *data, t_token **tokens);

void    free_tokens(t_token **tokens);
void    fill_nodes(t_data *data, t_token **tokens, char *input);
void    print_node(t_data *data);

int     outfile_counter(t_token **tokens);
int     infile_counter(t_token **tokens);
int     operator_counter(t_token **tokens);

int     first_token_controller(t_token **tokens);

int	    ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strjoin(char const *s1, char const *s2);

int     find_env(t_data *data, t_globals *globals);

void    free_array(void **array);
void    data_free(t_data *data);

int     is_input(char *cmd);


int     executor(t_data *data, t_globals *globals, char **envp);

void    op_router(t_data *data, int i);

int     **pipe_create(int pipe_count);
void    close_pipes(int **pipes, int pipe_count);
pid_t   *pid_create(int size);


void built_in(t_data *data, t_globals *globals, t_env **env, t_export **exp_list);

void	run_cd(t_data *data, int i);
char    *return_pwd(void);
void    run_pwd(void);
void    run_exit(t_data *data);
void    run_echo(t_data *data, int i);
void	run_unset(t_env **env, t_export **exp_list, int i, t_data *data);

char	*get_env_val(const char *key, t_env *env_list);
t_env	*load_environment(char *envp[]);

void    run_env(t_env *env_list);
void    run_export(t_export **exp_list, int i, t_data *data, t_env **env);
void	add_export(int i, t_data *data, t_export **exp_list, int j);
void 	add_env(int i, t_data *data, t_env **env_list, int j);

t_env	*create_env_node(const char *key, const char *value);
void	add_env_node(t_env **head, const char *key, const char *value);
t_env	*find_env_node(t_env *head, const char *key);
void	free_env_list(t_env *head);
char	*join_env(const char *key, const char *value);
t_env	*load_environment(char *envp[]);
char	*get_env_val(const char *key, t_env *env_list);
char	**get_env_arr(t_env *head);
void	update_env_node(t_env *head, const char *key, const char *new_value);
void	delete_env_node(t_env **head, const char *key);
void	print_list(t_env *head);

t_export	*create_export_node(const char *key, const char *value);
void	    add_export_node(t_export **head, const char *key, const char *value);
t_export	*find_export_node(t_export *head, const char *key);
void	    free_export_list(t_export *head);
char	    *join_export(const char *key, const char *value);
t_export	*load_export(char *envp[]);
char	    *get_export_val(const char *key, t_export *exp_list);
char	    **get_export_arr(t_export *head);
void	    update_export_node(t_export *head, const char *key, const char *new_value);
void	    delete_export_node(t_export **head, const char *key);
void	    print_export_list(t_export *head);

#endif

