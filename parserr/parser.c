#include "minishell.h"

/*void fill_node(t_node *node, t_token **tokens) 
{
    int i;

    i = 0;
    while (tokens[i]->type != TOKEN_PIPE && tokens[i]->type != TOKEN_EOF) 
    {
        if (tokens[i]->type == TOKEN_WORD)
        {
            node[i].cmd = tokens[0]->value;
            node[i].args = 
        }
        else if (tokens[i]->type == TOKEN_I || tokens[i]->type == TOKEN_I_I)
            node[i].infile[i] = tokens[i]->value;
        else if (tokens[i]->type == TOKEN_O || tokens[i]->type == TOKEN_O_O)
            node[i].outfile[i] = tokens[i]->value;
        i++;
    }
}*/

/*void fill_node(t_node *node, t_token **tokens) 
{
    int i = 0;
    int arg_index = 0;

    node->args = malloc(sizeof(char *) * 100);
    node->infile = malloc(sizeof(char *) * 100);
    node->outfile = malloc(sizeof(char *) * 100);

    while (tokens[i]->type != TOKEN_PIPE && tokens[i]->type != TOKEN_EOF) 
    {
        if (tokens[i]->type == TOKEN_WORD)
        {
            if (node->cmd == NULL) 
                node->cmd = tokens[i]->value;
            else 
                node->args[arg_index++] = tokens[i]->value;
        }
        else if (tokens[i]->type == TOKEN_I || tokens[i]->type == TOKEN_I_I)
            *node->infile = tokens[++i]->value;
        else if (tokens[i]->type == TOKEN_O || tokens[i]->type == TOKEN_O_O)
            *node->outfile = tokens[++i]->value;
        i++;
    }
    node->args[arg_index] = NULL;
}
*/

/*void fill_nodes(t_data *data, t_token **tokens) 
{
    int i = 0;
    int node_index;
    int arg_index;

    node_index = 0;
    arg_index = 0;
    data->nodes = malloc(sizeof(t_node) * (data->pipe_count + 1));
    for (int j = 0; j < data->pipe_count + 1; j++) 
    {
        data->nodes[j].args = malloc(sizeof(char *) * 100);
    }

    while (tokens[i]->type != TOKEN_EOF) 
    {
        if (tokens[i]->type == TOKEN_WORD) 
        {
            data->nodes[node_index].args[arg_index] = tokens[i]->value;
            arg_index++;
        } 
        else if (tokens[i]->type == TOKEN_PIPE) 
        {
            data->nodes[node_index].args[arg_index] = NULL;
            arg_index = 0;
            node_index++;
        }
        i++;
    }
    data->nodes[node_index].args[arg_index] = NULL; 
}*/

/*void fill_nodes(t_data *data, t_token **tokens) 
{
    int i = 0;
    int node_index = 0;
    int arg_index = 0;

    data->nodes = malloc(sizeof(t_node) * (data->pipe_count + 1));
    for (int j = 0; j < data->pipe_count + 1; j++) 
    {
        data->nodes[j].args = malloc(sizeof(char *) * 100);
    }

    while (tokens[i]->type != TOKEN_EOF) 
    {
        if (tokens[i]->type == TOKEN_WORD) 
        {
            if (arg_index == 0) 
                data->nodes[node_index].cmd = tokens[i]->value;
            else 
            {
                data->nodes[node_index].args[arg_index] = tokens[i]->value;
            }
            arg_index++;
        } 
        else if (tokens[i]->type == TOKEN_PIPE) 
        {
            data->nodes[node_index].args[arg_index] = NULL;
            arg_index = 0;
            node_index++;
        }
        i++;
    }
    data->nodes[node_index].args[arg_index - 1] = NULL;
}*/

/*void fill_nodes(t_data *data, t_token **tokens) 
{
    int i = 0;
    int node_index = 0;
    int arg_index = 0;

    data->nodes = malloc(sizeof(t_node) * (data->pipe_count + 1));
    for (int j = 0; j < data->pipe_count + 1; j++) 
    {
        data->nodes[j].cmd = malloc(sizeof(char) * 100);
        data->nodes[j].args = malloc(sizeof(char *) * 100);
        data->nodes[j].outfile = malloc(sizeof(char *) * 100);
        data->nodes[j].infile = malloc(sizeof(char *) * 100);
    }

    int y = 0;
    int x = 0;
    while (tokens[i]->type != TOKEN_EOF) 
    {
        if (tokens[i]->type == TOKEN_WORD) 
        {
            if (arg_index == 0) 
                data->nodes[node_index].cmd = tokens[i]->value;
            else
                data->nodes[node_index].args[arg_index] = tokens[i]->value;
            arg_index++;
        } 
        else if (tokens[i]->type == TOKEN_PIPE) 
        {
            data->nodes[node_index].args[arg_index] = NULL;
            arg_index = 0;
            node_index++;
        }
        else if (tokens[i]->type == TOKEN_O || tokens[i]->type == TOKEN_O_O) 
        {

            i++;
            data->nodes[node_index].outfile[y] = tokens[i]->value;
            y++;
        }
        else if (tokens[i]->type == TOKEN_I || tokens[i]->type == TOKEN_I_I)
        {
            i++;
            data->nodes[node_index].infile[x] = tokens[i]->value;
            x++;
        }
        i++;
    }
    data->nodes[node_index].args[arg_index] = NULL;
}*/

void fill_nodes(t_data *data, t_token **tokens) 
{
    int i = 0;
    int node_index = 0;
    int arg_index = 0;

    data->nodes = malloc(sizeof(t_node) * (data->pipe_count + 1));
    for (int j = 0; j < data->pipe_count + 1; j++) 
    {
        data->nodes[j].cmd = calloc(100, sizeof(char));
        data->nodes[j].args = calloc(100, sizeof(char *));
        data->nodes[j].outfile = calloc(100, sizeof(char *));
        data->nodes[j].infile = calloc(100, sizeof(char *));
    }


    int y = 0;
    int x = 0;
    while (tokens[i]->type != TOKEN_EOF) 
    {
        printf("HELLO! i: %d\n", i);
        if (tokens[i]->type == TOKEN_WORD)
        {
            if (arg_index == 0)
            {
                printf("cmd:\n");
                data->nodes[node_index].cmd = tokens[i]->value;
                arg_index++;
                printf("başaramadık abi\n");
            }
            else
            {
                printf("-li args\n");
                data->nodes[node_index].args[arg_index] = tokens[i]->value;
                printf("bastırması lazım %s\n", data->nodes[node_index].args[arg_index]);
                arg_index++;
            }
          
        }
        else if (tokens[i]->type == TOKEN_I || tokens[i]->type == TOKEN_I_I)
        {
            printf("INPUT FILE\n");
            data->nodes[node_index].infile[x] = tokens[i + 1]->value;
            x++;
        }
        else if (tokens[i]->type == TOKEN_O || tokens[i]->type == TOKEN_O_O)
        {
            printf("OUTPUT FILE\n");
            data->nodes[node_index].outfile[y] = tokens[i + 1]->value;
            y++;
        }
        else if (tokens[i]->type == TOKEN_PIPE)
        {
            printf("PIPE\n");
            data->nodes[node_index].args[arg_index + 1] = NULL;
            node_index++;
            arg_index = 0;
            x = 0;
            y = 0;
        }
        i++;
        printf("asfdasdasf\n");
    }
    printf("ÜST\n");
    data->nodes[node_index].args[arg_index + 1] = NULL;
    printf("ALT\n");
    
}


void print_node(t_data *data) 
{
        printf("CMD 1: %s\n", data->nodes[0].cmd);
        printf("NODE[0].ARGS[1]: %s\n", data->nodes[0].args[1]);
        printf("OUTFILE:%s\n", data->nodes[0].outfile[0]);
        printf("CMD 2:%s\n", data->nodes[1].cmd);
        printf("NODE[1].ARGS:%s\n", data->nodes[1].args[1]);
        printf("CMD 2: %s\n", data->nodes[1].cmd);
        printf("NODE[1].ARGS[1]: %s\n", data->nodes[1].args[1]);
        printf("NODE[1].OUTFILE %s\n", data->nodes[1].outfile[0]);
        printf("CMD 3: %s\n", data->nodes[2].cmd);
        printf("NODE[2].ARGS: %s\n", data->nodes[2].args[1]);
        printf("NODE[2].OUTFILE: %s\n", data->nodes[2].outfile[0]);
        printf("NODE[2].OUTFILE: %s\n", data->nodes[2].outfile[1]);
        printf("NODE[2].OUTFILE: %s\n", data->nodes[2].outfile[2]);
}

void    fill_operators(t_token **tokens, t_data *data)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (tokens[i]->type != TOKEN_EOF)
    {
        if (tokens[i]->type != TOKEN_WORD)
        {
            data->operators[i] = tokens[i]->value;
        }
        i++;
    }
}

void print_operators(t_data *data)
{
    int i;

    i = 0;
    while (data->operators[i])
    {
        printf("%s\n", data->operators[i]);
        i++;
    }
}