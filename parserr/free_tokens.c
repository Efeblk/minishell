#include "minishell.h"

void free_tokens(t_token **tokens)
{
    int i = 0;

    while (tokens[i])
    {
        if (tokens[i]->value)
        {
            free(tokens[i]->value);
        }
        free(tokens[i]);
        i++;
    }
    
    // Free the array of pointers
    free(tokens);
}
