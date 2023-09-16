#include "minishell.h"

int pipe_count(char *input, t_data *data)
{
    int i;
    int start;

    i = 0;
    while ((input[i] > 9 && input [i] < 13) || input[i] == 32)
        i++;
    start = i;
    if (input[start] == '|')
    {
        if (input[start + 1] == '|')
            printf("syntax error near unexpected token `||'\n");
        else
            printf("syntax error near unexpected token `|'\n");
        exit(1);
    }
    else
    {
        while (input[i])
        {
            if (input[i] == '|')
            {
                if (input[i + 1] == '|')
                    printf("");
                else
                {
                    data->pipe_count++;
                    while ((input[i] > 9 && input [i] < 13) || input[i] == 32)
                        i++;
                    if (input[i] == '|')
                    {
                        printf("syntax error\n");
                        exit(1);
                    }
                }
                i++;
            }
        }
    }
    return (data->pipe_count);
}   

void    ft_readline(t_data *data)
{
    char    *input;
    char    *str;
    int     i;

    i = 0;
    data->pipe_count = 0;
    input = readline("Enter a command: ");
    add_history(input);
    str = input;
    data->pipe_count = pipe_count(str, data);
    free(input);
}



int main() 
{
    t_data data;
    int       i;

    i = 0;
    ft_readline(&data);
    printf("%d\n", data.pipe_count);

    return (0);
}