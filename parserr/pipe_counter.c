#include "minishell.h"

int pipe_counter(t_data *data, t_token **tokens)
{
    int i;

    i = 0;
    data->pipe_count = 0;
    while (tokens[i]->type != TOKEN_EOF)
    {
        if (tokens[i]->type == TOKEN_PIPE)
            data->pipe_count++;
        i++;
    }
    return (data->pipe_count);
}