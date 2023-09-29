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

t_token **resize_tokens(t_token **tokens, int old_size, int new_size) 
{
    t_token **new_tokens;
    int i;

    i = 0;
    new_tokens  = malloc(sizeof(t_token *) * new_size);
    if (new_tokens == NULL)
    {
        printf("Memory allocation failed\n");
        exit(1);
    }
    while (i < old_size)
    {
        new_tokens[i] = tokens[i];
        i++;
    }
    free_tokens(tokens);
    return (new_tokens);
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
<<<<<<< HEAD
=======
    //printf("%d\n",size);
>>>>>>> ed1ead81774cabb62e559dd07ec1e66fa56d7861
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

int    ft_readline(t_data *data)
{
        char *input;
        //int count1;
        t_token **tokens;

        input = readline("Enter a command: ");

        if (input[0] == '\0' )
        {
            free(input);
            return (0);
        }
        add_history(input);
        tokens = tokenize_input(input);
        //print_and_free_tokens(tokens, count);
        data->pipe_count = pipe_counter(data, tokens);
        fill_nodes(data, tokens, input);
        free(input);
         
        return (1);
}
