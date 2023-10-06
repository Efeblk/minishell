/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alakin <alakin@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 19:57:40 by alakin            #+#    #+#             */
/*   Updated: 2023/10/07 00:42:16 by alakin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*ft_realloc(void *ptr, size_t b_amount, size_t b_size)
{
	void	*rt;
	int		msize;

	msize = b_amount * b_size;
	rt = malloc((b_amount + 1) * b_size);
	rt = ft_memcpy(rt, ptr, msize);
	free(ptr);
	return (rt);
}

char	*get_expanded(const char *str, t_env **env_list)
{
	exp_stsh	*stsh;
	int			sf;
	int			df;
	char		*rt;

	stsh = get_stsh(str);
	sf = 0;
	df = 0;
	expand_stsh(str, stsh, sf, df, env_list);
	free((char *)str);
	rt = stsh->rt;
	free(stsh);
	return (rt);
}

void	expand_stsh(const char *str, exp_stsh *stsh,int sf, int df, t_env **env_list)
{
	while (str[stsh->src_i])
	{
		if (str[stsh->src_i] == '"' && !sf)
			df = !df;
		else if (str[stsh->src_i] == '\'' && !df)
			sf = !sf;
		else if (str[stsh->src_i] == '$' && !sf)
		{
				ft_dollarize(str, stsh, env_list);
		}
		else
		{
			stsh->rt[stsh->rt_i++] = str[stsh->src_i];
		}
		stsh->src_i++;
	}
	stsh->rt[stsh->rt_i] = '\0';
}

void	ft_dollarize(const char *str, exp_stsh *stsh, t_env **env_list)
{
	int		var_start;
	int		var_len;
	char	*var_name;
	char	*var_val;

	var_start = stsh->src_i + 1;
	var_len = 0;
	while (str[var_start + var_len] != '\0' &&
	(isalnum(str[var_start + var_len]) ||
	str[var_start + var_len] == '_'))
	{
		var_len++;
	}
	var_name = (char *)malloc(var_len + 1);
	strncpy(var_name, str + var_start, var_len);
	var_name[var_len] = '\0';
	var_val = get_env_val(var_name, *env_list);
	free(var_name);
	if (var_val)
	{
		stsh->rt_len += strlen(var_val) - (1 + var_len);
		stsh->rt = (char *)ft_realloc(stsh->rt, stsh->rt_len, sizeof(char));
		strcpy(stsh->rt + stsh->rt_i, var_val);
		stsh->rt_i += strlen(var_val);
	}
	stsh->src_i += var_len;
}

exp_stsh	*get_stsh(const char *str)
{
	exp_stsh	*rt;

	rt = (exp_stsh *)malloc(sizeof(exp_stsh));
	rt->rt_i = 0;
	rt->src_i = 0;
	rt->src_len = strlen(str);
	rt->rt_len = rt->src_len;
	rt->rt = (char *)malloc(sizeof(char) * (rt->rt_len + 1));
	return (rt);
}

t_token	**allocate_tokens(int size)
{
	t_token	**tokens;

	tokens = malloc(sizeof(t_token *) * size);
	if (tokens == NULL)
	{
		printf("Memory allocation failed\n");
		exit(1);
	}
	return (tokens);
}

int	count_tokens(char *input)
{
	int		count;
	t_token	*token;

	count = 0;
	while (1) 
	{
		token = get_next_token(&input);
		count++;
		if (token->type == TOKEN_EOF)
		{
			free(token->value);
			free(token);
			break ;
		}
		free(token->value);
		free(token);
	}
	return (count);
}

t_token	**tokenize_input(char *input)
{
	int			size;
	t_token		**tokens;
	t_token		*token;
	int			i;

	i = 0;
	size = count_tokens(input);
	tokens = allocate_tokens(size);
	while (1)
	{
		token = get_next_token(&input);
		tokens[i] = malloc(sizeof(t_token));
		tokens[i]->type = token->type;
		tokens[i]->value = ft_strdup(token->value);
		i++;
		if (token->type == TOKEN_EOF)
		{
			free(token->value);
			free(token);
			break ;
		}
		free(token->value);
		free(token);
	}
	return (tokens);
}

int	first_token_controller(t_token **tokens)
{
	if (tokens[0]->type == TOKEN_PIPE)
	{
		printf("syntax error near unexpected token `|'\n");
		return (0);
	}
	else if ((tokens[0]->type == TOKEN_I || tokens[0]->type == TOKEN_I_I ||
		tokens[0]->type == TOKEN_O ||
			tokens[0]->type == TOKEN_O_O) && tokens[1]->type == TOKEN_EOF)
	{
		printf("syntax error near unexpected token `newline' \n");
		return (0);
	}
	else
		return (1);
}

int	controller(t_token **tokens, int i)
{
	if (tokens[i + 1]->type == TOKEN_PIPE)
	{
		printf("syntax error near unexpected token `|'\n");
        return (0);
    }
    else if (tokens[i + 1]->type == TOKEN_I)
    {
        printf("syntax error near unexpected token '<'\n");
        return (0);
    }
    else if (tokens[i + 1]->type == TOKEN_I_I)
    {
        printf("syntax error near unexpected token '<<'\n");
        return (0);
    }
    else if (tokens[i + 1]->type == TOKEN_O)
    {
        printf("syntax error near unexpected token '>'\n");
        return (0);
    }
    else if (tokens[i + 1]->type == TOKEN_O_O)
    {
        printf("syntax error near unexpected token '>>'\n");
        return (0);
    }
        return (1);
}

int     token_controller(t_token **tokens)
{
    int i;

    i = -1;
    while (tokens[++i]->type != TOKEN_EOF)
    {
        if (tokens[i]->type == TOKEN_PIPE)
        {
            if (!controller(tokens, i))
                return (0);
        }
        else if (tokens[i]->type == TOKEN_I)
        {
            if (!controller(tokens, i))
                return (0);
        }
        else if (tokens[i]->type == TOKEN_I_I)
        {
           if (!controller(tokens, i))
                return (0);
        }
        else if (tokens[i]->type == TOKEN_O)
        {        
            if (!controller(tokens, i))
                return (0);
        }
        else if (tokens[i]->type == TOKEN_O_O)
        {
            if (!controller(tokens, i))
                return (0);
        }
    }
    return (1);
}

char	*full_pwd(t_globals *globals)
{
	char	*pwd;
	char	*suffix;
	char	*user;
	char	*print;
	char	*env;

	env = globals->user;
	pwd = return_pwd();
	suffix = ft_strjoin(pwd, ":>");
	user = ft_strjoin(env, "@");
	print = ft_strjoin(user, suffix);

	free(pwd);
	free(user);
	free(suffix);
	pwd = NULL;
	suffix = NULL;
	user = NULL;
	env = NULL;
	return (print);
}

int     ft_readline(t_data *data, t_globals *globals, t_env **env_list, t_index *index)
{
        char *input;
        t_token **tokens;
        
        char *print = full_pwd(globals);
        input = readline(print);
        add_history(input);
        if (input[0] == '\0')
        {
            free(print);
            print = NULL;
            free(data);
            free(input);
            return (0);
        }
        input = get_expanded(input, env_list);
        tokens = tokenize_input(input);
        if (!first_token_controller(tokens))
        {
            free(print);
            print = NULL;
            free_tokens(tokens);
            free(input);
            free(data);
            return (0);
        }
        if (!token_controller(tokens))
        {
            free(print);
            print = NULL;
            free_tokens(tokens);
            free(input);
            free(data);
            return (0);
        }
        data->pipe_count = pipe_counter(data, tokens);
        if (!fill_nodes(data, tokens, input, index))
        {
            free(print);
            free_tokens(tokens);
            free(input);
            data_free(data);
            return (0);
		}
        free(input);
        free(print);
        print = NULL;
        return (1);
}
