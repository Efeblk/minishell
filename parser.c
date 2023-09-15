#include "minishell.h"

char    **parse_word(t_data data)
{
    
}

void    ft_readline(t_data *data)
{
    char    *input;
    char    *str;
    int     i;

    i = 0;
    input = readline("Enter a command: ");
    add_history(input);
    str = input;
    free(input);
}

int arg_count(t_data *data)
{
    int i;

    i = 0;
    while (data->nodes->args[i])
        i++;
    return (i);
}

int pipe_count(char *input, t_data *data)
{
    int i;

    i = 0;
    data->pipe_count = 0;
    while (input[i])
    {
        if (input[i] == '|')
            data->pipe_count++;
        i++;
    }
    return (data->pipe_count);
}


int main() 
{
    t_data data;
    int       i;

    i = 0;
    ft_readline(&data);

    return (0);
}