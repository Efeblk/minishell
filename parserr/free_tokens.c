#include "minishell.h"

void free_tokens(t_token **tokens)
{
    int i = 0;

    while (tokens[i]->type != TOKEN_EOF)
    {
        free(tokens[i]->value);
        free(tokens[i]);
        i++;
    }
    free(tokens[i]);
    free(tokens); 
}