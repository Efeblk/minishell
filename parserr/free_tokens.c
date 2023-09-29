#include "minishell.h"

void free_tokens(t_token **tokens)
{
    int i = 0;
    printf("TOKENS[0]: %s \n", tokens[0]->value);
    printf("TOKENS[1]: %s \n", tokens[1]->value);

    while (tokens[i]->type != TOKEN_EOF)
    {
        printf("qqq\n");

        free(tokens[i]->value);
        free(tokens[i]);
        
        i++;
    }
    free(tokens[i]);

    printf("TOKENS: %lu \n", sizeof(tokens));
    

    // Free the array of pointers
    free(tokens); 
}