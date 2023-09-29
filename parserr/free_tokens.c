#include "minishell.h"

void free_tokens(t_token **tokens)
{
<<<<<<< HEAD
    int i = 0;
=======
    int i;
>>>>>>> ed1ead81774cabb62e559dd07ec1e66fa56d7861

    i = 0;
    while (tokens[i]->type != TOKEN_EOF)
    {
        free(tokens[i]->value);
        free(tokens[i]);
        i++;
    }
    free(tokens[i]->value);
    free(tokens[i]);
    free(tokens); 
}