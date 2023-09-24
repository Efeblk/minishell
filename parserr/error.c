
#include "minishell.h"

/*void    token_controller(t_token **tokens)
{
    int i;

    i = 0;

    first_token_controller(tokens);
    while (tokens[i]->type != TOKEN)
    {

    }
}
*/

void    first_token_controller(t_token **tokens)
{
    if (tokens[0]->type == TOKEN_PIPE)
        printf("syntax error near unexpected token `|'\n");
    else if (tokens[0]->type == TOKEN_I || tokens[0]->type == TOKEN_I_I || tokens[0]->type == TOKEN_O || tokens[0]->type == TOKEN_O_O)
        printf("syntax error near unexpected token `newline'\n");
}

