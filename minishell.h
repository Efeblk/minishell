
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
# include <limits.h>

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
	TokenType	type;
	char		*value;
} t_token;

typedef struct s_env
{
	char    *key;
	char    *value;
	char    *full;
	struct  s_env *next;
} t_env;

typedef struct s_export
{
	char	*key;
	char	*value;
	char	*full;
	struct s_export	*next;
} t_export;

typedef struct s_node
{
	char	*cmd;
	char	**args;
	char	**outfile;
	char	**infile;
	int		is_pipe;
	char	**operators;
	int		arg_count;
	int		is_builtin;
	int		is_valid_cmd;
	int		is_valid_path;
}t_node;

typedef struct s_data
{
	int		pipe_count;
	t_env	*env;
	t_node	*nodes;
	int		count;
}t_data;

typedef struct s_globals
{
	char	*user;
	int		shell_count;
	int		status;
}t_globals;

typedef struct s_exp_stsh
{
	int		src_i;
	int		rt_i;

	int		src_len;
	int		rt_len;

	char	*rt;

}	t_exp_stsh;

typedef struct s_index
{
	int	node_index;
	int	arg_index;
	int	current_index;
	int	i;
	int	x;
	int	y;
}	t_index;

int	ft_readline(t_data *data, t_globals *globals,
	t_env **env_list, t_index *index);
char	*ft_strdup(const char *s1);
char	**ft_split(const char *s, char c);
char	*ft_itoa(int n);
int		ft_atoi(const char *str);
char	*ft_substr(char const *s, unsigned int start, size_t len);
size_t	ft_strlen(const char *s);
char	*ft_strchr(const char *s, int c);
t_token	*get_next_token(char **input);
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
int	    fill_nodes(t_data *data, t_token **tokens, char *input, t_index *index);
void    print_node(t_data *data);

int     outfile_counter(t_token **tokens);
int     infile_counter(t_token **tokens);
int     operator_counter(t_token **tokens);

int     first_token_controller(t_token **tokens);
int     controller(t_token **tokens, int i);
int     token_controller(t_token **tokens);

char	*ft_strjoin(char const *s1, char const *s2);

int     find_env(t_data *data, t_env **env);

void    free_array(void **array);
void    data_free(t_data *data);

int     is_input(char *cmd);

int     executor(t_data *data, t_env **env);
void    op_router(t_data *data, int i);
int     **pipe_create(int pipe_count);
void    close_pipes(int **pipes, int pipe_count);
pid_t   *pid_create(int size);
void built_in(t_data *data, t_env **env, t_export **exp_list);
void	run_cd(t_data *data, int i);
char    *return_pwd(void);
void    run_pwd(void);
void    run_exit(t_data *data, t_env **env, int i);
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

void        update_status(int status, t_env **env);
int         find_heredoc(char **operators);
void	wait_close_free(t_data *data, int **pipes, int *pids, t_env **env);
int     question_mark(t_data *data, t_env **env);
char	    *get_expanded(const char *str, t_env **env_list);
void	    expand_stsh(const char *str, t_exp_stsh *stsh, int sf, int df, t_env **env_list);
void	    ft_dollarize(const char *str, t_exp_stsh *stsh, t_env **env_list);
t_exp_stsh	*get_stsh(const char *str);
void	    *ft_realloc(void *ptr, size_t b_amount, size_t b_size);

int		ft_strcmp(const char *s1, const char *s2);

void	fill_cmd(t_data *data, t_token **tokens, t_index *index);
void	fill_structs(t_data *data, t_token **tokens, char *input, t_index *index);
void	fill_index(t_index *index);
int	    fill_infile(t_data *data, t_token **tokens, t_index *index);
int	    fill_outfile(t_data *data, t_token **tokens, t_index *index);
void	pipe_situation(t_data *data, t_index *index);
void	null_free_nodes(t_data *data, t_token **tokens, t_index *index);
void	control_word(t_data *data, t_token **tokens, t_index *index);
void     update_status(int status, t_env **env);
t_token	*input_utils(char **input);
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strncpy(char *dest, const char *src, size_t n);
char	*ft_strcpy(char *s1, char *s2);
int		ft_isalnum(int c);
void	cmd_free(t_data *data, int i);
void	args_free(t_data *data, int i, int j);
void	outfile_free(t_data *data, int i, int j);
void	infile_free(t_data *data, int i, int j);
void	operators_free(t_data *data, int i, int j);
void	last_controller(t_data *data, t_token **tokens, t_index *index);
int	    pipe_controller_printer(t_token **tokens, int i);
int	    input_check(char *input, char *print, t_data *data);
void	free_main(t_token **tokens, char *input, t_data *data, char *print);
void    free_main2(t_token **tokens, char *input, t_data *data, char *print);
char	*full_pwd(t_globals *globals);
int		token_controller_2(t_token **tokens, int i);
void	readline_fill(char *print, char *input, t_globals *globals);
void	readline_free(char *input, char *print);
int	    main_controller(t_data *data, t_token **tokens, char *input, char *print);

#endif
