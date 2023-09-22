#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>

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
    return tokens;
}

t_token **resize_tokens(t_token **tokens, int size) 
{
    t_token **new_tokens;

    new_tokens  = malloc(sizeof(t_token *) * size);
    if (new_tokens == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    memcpy(new_tokens, tokens, size / 2 * sizeof(t_token *));
    free(tokens);
    return new_tokens;
}

t_token **tokenize_input(const char *input, int *count) 
{
    int size;
    t_token **tokens;

    size = 10;
    *count = 0; 
    tokens = allocate_tokens(size);

    while (1) 
    {
        t_token *token; 

        token = get_next_token(&input);
        if (*count >= size) 
        {
            size *= 2;
            tokens = resize_tokens(tokens, size);
        }
        tokens[(*count)++] = token;
        if (token->type == TOKEN_EOF)
            break;
    }
    return (tokens);
}

void print_and_free_tokens(t_token **tokens, int count) 
{
    int i;

    i = 0;
    while (i < count)
    {
        printf("Token %d: Type %d, Value %s\n", i, tokens[i]->type, tokens[i]->value);
        i++;
    }
}

int main() 
{
    while (1) 
    {
        const char *input;
        int count;
        t_token **tokens;

        input = readline("Enter a command: ");
        add_history(input);
        tokens = tokenize_input(input, &count);
        print_and_free_tokens(tokens, count);
    }

    return 0;
}
