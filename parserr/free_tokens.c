#include "minishell.h"

void    free_tokens(t_token **tokens)
{
    int i;

    i = -1;
    while (tokens[++i])
        free(tokens[i]->value);
    free(tokens);
}