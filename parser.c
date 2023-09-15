#include "minishell.h"



void    ft_readline(t_node *node)
{
    char    *input;
    int     i;

    i = 0;
    input = readline("Enter a command: ");
    node->args = ft_split(input, ' ');
    node->infile = NULL;
    node->outfile = NULL;
    node->pipe_count = pipe_count(input, node);
    add_history(input);
    free(input);
}

int arg_count(t_node *node)
{
    int i;

    i = 0;
    while (node->args[i])
        i++;
    return (i);
}
int pipe_count(char *input, t_node *node)
{
    int i;

    i = 0;
    node->pipe_count = 0;
    while (input[i])
    {
        if (input[i] == '|')
            node->pipe_count++;
        i++;
    }
    return (node->pipe_count);
}


int main() 
{
    t_node node;
    int       i;

    i = 0;
    node.pipe_count = 0;
    ft_readline(&node);

    return (0);
}