#include "minishell.h"

static int outfiler(char **outfiles, char **operators, int *j)
{
    int i;
    int fd;

    i = -1;

    while (outfiles[++i] && (((ft_strncmp(operators[i], ">", 1)) == 0) || ((ft_strncmp(operators[i], ">>", 2)) == 0)))
    {
        if ((ft_strncmp(operators[i], ">", 2)) == 0)
        {
            fd = open(outfiles[i], O_WRONLY | O_CREAT | O_TRUNC , 0777);
        }
        else if ((ft_strncmp(operators[i], ">>", 2)) == 0)
        {
            fd = open(outfiles[i], O_WRONLY | O_CREAT | O_APPEND, 0777);
        }
        (*j)++;
    }
    (*j)--;
    return(fd);
}

static void here_doc(t_data *data, int i)
{
    FILE *tmp = tmpfile();
    char buffer[1024];
    char *delimiter = data->nodes[i].infile[0];

    // Read from stdin until the delimiter is found
    while (fgets(buffer, sizeof(buffer), stdin) != NULL)
    {
        if (strncmp(buffer, delimiter, strlen(delimiter)) == 0)
            break;
        fputs(buffer, tmp);
    }

    // Redirect stdin to the temporary file
    fflush(tmp);
    rewind(tmp);
    dup2(fileno(tmp), STDIN_FILENO);

    // Execute the command
    execve(data->nodes[i].args[0], data->nodes[i].args, NULL);
    
}

void op_router(t_data *data, int i)
{
    int j = -1;

    while (data->nodes[i].operators[++j] != NULL)
    {
        if (ft_strncmp(data->nodes[i].operators[j], ">", 2) == 0)
        {
            dup2(outfiler(data->nodes[i].outfile, data->nodes[i].operators, &j), STDOUT_FILENO);
        }
        else if (ft_strncmp(data->nodes[i].operators[j], ">>", 2) == 0)
        {
            dup2(outfiler(data->nodes[i].outfile, data->nodes[i].operators, &j), STDOUT_FILENO);
        }
        else if (ft_strncmp(data->nodes[i].operators[j], "<", 2) == 0)
        {
            dup2(open(data->nodes[i].infile[0], O_RDONLY, 0777), STDIN_FILENO);
        }
        else if (ft_strncmp(data->nodes[i].operators[j], "<<", 2) == 0)
        {   
            here_doc(data, i);
        }
    }
}