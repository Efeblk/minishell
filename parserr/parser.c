#include "minishell.h"

int outfile_counter(t_token **tokens)
{
    int i;
    int count;
    
    i = 0;
    count = 0;
    while (tokens[i]->type != TOKEN_EOF)
    {
        if (tokens[i]->type == TOKEN_O || tokens[i]->type == TOKEN_O_O)
            count++;
        i++;
    }
    return (count);
}

int infile_counter(t_token **tokens)
{
    int i;
    int count;
    
    i = 0;
    count = 0;
    while (tokens[i]->type != TOKEN_EOF)
    {
        if (tokens[i]->type == TOKEN_I || tokens[i]->type == TOKEN_I_I)
            count++;
        i++;
    }
    return (count);
}

int operator_counter(t_token **tokens)
{
    int i;
    int count;
    
    i = 0;
    count = 0;
    while (tokens[i]->type != TOKEN_EOF)
    {
        if (tokens[i]->type != TOKEN_WORD)
            count++;
        i++;
    }
    return (count);
}

void    fill_structs(t_data *data, t_token **tokens, char *input)
{
    int i;

    i = 0;
    data->nodes = malloc(sizeof(t_node) * (data->pipe_count + 1));
    while (i < (data->pipe_count + 1))
    {
        data->nodes[i].args = calloc(sizeof(input), sizeof(char *));
        data->nodes[i].outfile = calloc((outfile_counter(tokens) + 1), sizeof(char *));
        data->nodes[i].infile = calloc((infile_counter(tokens) + 1), sizeof(char *));
        data->nodes[i].operators = calloc((operator_counter(tokens) + 1), sizeof(char *));       
        i++;
    }
}

int    fill_nodes(t_data *data, t_token **tokens, char *input)
{
    int i;
    int node_index;
    int arg_index;
    int y;
    int x;

    i = 0;
    node_index = 0;
    arg_index = 0;
    y = 0;
    x = 0;
    int current_index = 0;
    fill_structs(data, tokens, input);
    while (tokens[i]->type != TOKEN_EOF)
    {
        data->nodes[node_index].is_pipe = 0;
        if (tokens[0]->type != TOKEN_WORD)
            data->nodes[node_index].cmd = NULL;
        if (tokens[i]->type == TOKEN_WORD)
        {
            if (arg_index == 0)
            {
                    data->nodes[node_index].cmd = ft_strdup(tokens[i]->value);
                    arg_index++;
            }
            else
            {
                data->nodes[node_index].args[arg_index] = ft_strdup(tokens[i]->value);
                arg_index++;
            }
        }
        else if ((tokens[i]->type == TOKEN_I || tokens[i]->type == TOKEN_I_I))
        {
            if (tokens[i + 1]->type == TOKEN_EOF)
            {
                    printf("syntax error near unexpected token `newline\n'");
                    return (0);
            }
            else
            { 
                data->nodes[node_index].infile[x] = ft_strdup(tokens[i + 1]->value);
                data->nodes[node_index].operators[current_index] = ft_strdup(tokens[i]->value);
                current_index++;
                x++;
                i++;
            }
        }
        else if ((tokens[i]->type == TOKEN_O || tokens[i]->type == TOKEN_O_O) && (tokens[i + 1]->type != TOKEN_EOF))
        {
            if (tokens[i + 1]->type == TOKEN_EOF)
            {
                    printf("syntax error near unexpected token `newline\n'");
                    return (0);
            }
            else
            {
                data->nodes[node_index].outfile[y] = ft_strdup(tokens[i + 1]->value);
                data->nodes[node_index].operators[current_index] = ft_strdup(tokens[i]->value);
                current_index++;
                y++;
                i++;
            }
        }
        else if (tokens[i]->type == TOKEN_PIPE)
        {
                data->nodes[node_index].is_pipe = 1;
                data->nodes[node_index].args[arg_index + 1] = NULL;
                data->nodes[node_index].infile[x] = NULL;
                data->nodes[node_index].outfile[y] = NULL;
                data->nodes[node_index].operators[current_index] = NULL;
                node_index++;
                data->nodes[node_index].cmd = NULL;
                arg_index = 0;
                current_index = 0;
                x = 0;
                y = 0;
        }
        i++;
    }
    data->nodes[node_index].args[arg_index] = NULL;
    data->nodes[node_index].operators[current_index] = NULL;
    free_tokens(tokens);
    return (1);
}



// void print_node(t_data *data) 
// {
//     (void)data;
//         printf("CMD 1: %s\n", data->nodes[0].cmd);
//         printf("NODE[0].ARGS[1]: %s\n", data->nodes[0].args[1]);
//         printf("NODE[0].ARGS[2]: %s\n", data->nodes[0].args[2]);
//         printf("NODE[0].ARGS[3]: %s\n", data->nodes[0].args[3]);
//         //printf("OUTFILE:%s\n", data->nodes[0].outfile[0]);
//         //printf("CMD 2:%s\n", data->nodes[1].cmd);
//         //printf("OUTFILE[0]:%s\n", data->nodes[1].outfile[0]);
//         //printf("OUTFILE[1]:%s\n", data->nodes[1].outfile[1]);
//         //printf("OUTFILE[1]:%s\n", data->nodes[1].outfile[2]);
//         //printf("NODE[1].ARGS[1]:%s\n", data->nodes[1].args[1]);
//         //printf("NODE[1].ARGS[2]:%s\n", data->nodes[1].args[2]);
//         //printf("NODE[1].ARGS[3]:%s\n", data->nodes[1].args[3]);
//         //printf("NODE[1].INFILE:%s\n", data->nodes[1].infile[0]);
//         //printf("NODE[1].ARGS[1]: %s\n", data->nodes[1].args[1]);
//         //printf("NODE[1].OUTFILE %s\n", data->nodes[1].outfile[0]);
//         //printf("CMD 3: %s\n", data->nodes[2].cmd);
//         //printf("NODE[2].ARGS[1]: %s\n", data->nodes[2].args[1]);
//         //printf("NODE[2].ARGS[2]: %s\n", data->nodes[2].args[2]);
//         //printf("NODE[2].OUTFILE: %s\n", data->nodes[2].outfile[0]);
//         //printf("NODE[2].OUTFILE: %s\n", data->nodes[2].outfile[1]);
//         //printf("NODE[2].OUTFILE: %s\n", data->nodes[2].outfile[2]);
// }

/*void    fill_operators(t_token **tokens, t_data *data)
{
    (void)tokens;
    (void)data;
    return ;
}*/

/*void print_operators(t_data *data)
{
    (void)data;
    return ;
}*/