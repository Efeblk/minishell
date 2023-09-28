#include "minishell.h"

t_token *get_next_token(char **input)
{
    while (isspace(**input))
		(*input)++;
	if (**input == '\0')
		return (create_token(TOKEN_EOF, input, *input));
	if (**input == '<' || **input == '>' || **input == '|')
		return (generate_pr_token(input));
	return (generate_word_token(input));
}

t_token	*generate_word_token(char **input)
{
	char	*start;
	int				sf;
	int				df;

	start = *input;
	sf = 0;
	df = 0;
	while (**input)
	{
		if (!(sf || df) && (ft_strchr("<>|", **input) || isspace(**input)))
			break ;
		if (**input == '"' && !sf)
			df = !df;
		if (**input == '\'' && !df)
			sf = !sf;
		(*input)++;
	}
	if (sf != 0 || df != 0)
	{	
		printf("Error: Unbalanced quotes\n");
		exit(1);
	}
	return (create_token(TOKEN_WORD, input, start));
}


t_token	*generate_pr_token(char **input)
{
	if (**input == '|')
	{
		(*input)++;
		return (create_token(TOKEN_PIPE, input, (*input) - 1));
	}
	if (**input == '<')
	{
		(*input)++;
		if (**input == '<')
		{
			(*input)++;
			return (create_token(TOKEN_I_I, input, (*input) - 2));
		}
		return (create_token(TOKEN_I, input, (*input) - 1));
	}
	if (**input == '>')
	{
		(*input)++;
		if (**input == '>')
		{
			(*input)++;
			return (create_token(TOKEN_O_O, input, (*input) - 2));
		}
		return (create_token(TOKEN_O, input, (*input) - 1));
	}
	return (NULL);
}

char	*create_word(char **input, char *start)
{
	size_t	len;
	char	*word;

	len = *input - start;
	if (len == 0)
		return (ft_strdup(""));
	word = (char *) malloc(len + 1);
	strncpy(word, start, len);
	word[len] = '\0';
	return (word);
}


t_token	*create_token(TokenType type, char **input, char *start)
{
	t_token	*token;
	
	token = (t_token *) malloc(sizeof(t_token));
	token->type = type;
	token->value = create_word(input, start);
	return (token);
}