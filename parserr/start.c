#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

t_token **allocate_tokens(int size) 
{
    t_token **tokens;

    tokens =  malloc(sizeof(t_token *) * size);
    if (tokens == NULL) 
    {
        printf("Memory allocation failed\n");
        exit(1);
    }
    return (tokens);
}


int count_tokens(char *input) 
{
    int count;
    t_token *token;

    count = 0;
    while (1) 
    {
        token = get_next_token(&input);
        count++;
        if (token->type == TOKEN_EOF)
        {
            free(token->value);
            free(token);
            break;
        }
        free(token->value);
        free(token);
    }
    return (count);
}

t_token **tokenize_input(char *input) 
{
    int size;
    t_token **tokens;
    t_token *token; 
    int i;

    size = 0;
    i = 0;
    size = count_tokens(input);
    //printf("%d\n",size);
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
            break;
        }
        free(token->value);
        free(token);
    }
    return (tokens);
}



void print_and_free_tokens(t_token **tokens, int count) 
{
    int i;
    (void)tokens;
    i = 0;
    while (i < count - 1)
    {
        i++;
    }
}

int    first_token_controller(t_token **tokens)
{
    if (tokens[0]->type == TOKEN_PIPE)
    {
        printf("syntax error near unexpected token `|'\n");
        return (0);
    }
    else if ((tokens[0]->type == TOKEN_I || tokens[0]->type == TOKEN_I_I || tokens[0]->type == TOKEN_O || tokens[0]->type == TOKEN_O_O) && tokens[1]->type == TOKEN_EOF)
    {
        printf("syntax error near unexpected token `newline' \n");
        return (0);
    }
    else
        return (1);

}

int     token_controller(t_token **tokens)
{
    int i;

    i = 0;
    while (tokens[i]->type != TOKEN_EOF)
    {
        if (tokens[i]->type == TOKEN_PIPE)
        {
            if (tokens[i + 1]->type == TOKEN_PIPE)
            {
                printf("syntax error near unexpected token `|'\n");
                return (0);
            }
        }
        else if (tokens[i]->type == TOKEN_I)
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
        }
        else if (tokens[i]->type == TOKEN_I_I)
        {
            if (tokens[i + 1]->type == TOKEN_I)
            {
                printf("syntax error near unexpected token '<'\n");
                return (0);   
            }
            else if (tokens[i + 1]->type == TOKEN_I_I)
            {
                printf("syntax error near unexpected token '<<'\n");
                return (0);
            }
        }
        i++;
    }
    return (1);
}

char *full_pwd(t_globals *globals)
{
    char *pwd;
    char *suffix;
    char *user;
    char *print;
    char *env;

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
    return(print);
}

int     ft_readline(t_data *data, t_globals *globals)
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
        if (!fill_nodes(data, tokens, input))
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
