#include "minishell.h"

void    free_tokens(t_token **tokens)
{
    int i;

    i = 0;
    while (tokens[i++])
        free(tokens[i]);
    free(tokens);
}