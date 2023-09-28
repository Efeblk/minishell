#include "minishell.h"

void free_tokens(t_token **tokens)
{
    int i = 0;
    
    while (tokens[i]->type != TOKEN_EOF)
    {
        printf("qqq\n");
        if (tokens[i]->value)
        {
            free(tokens[i]->value);
            free(tokens[i]);
        }
        i++;
    }
    printf("TOKENS\n");
    // Free the array of pointers
    free(tokens); 
}