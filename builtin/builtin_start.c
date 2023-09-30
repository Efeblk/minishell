#include "minishell.h"

static void is_builtin(char *cmd, t_data *data)
{
    if (ft_strncmp(cmd, "clear", 5) == 0)
    {
        printf("\033[2J\033[H");
    }   
    else if (ft_strncmp(cmd, "exit", 4) == 0)
    {
        data_free(data);
        printf("exit");
        exit(0);
    }
    else if (ft_strncmp(cmd, "pwd", 3) == 0)
    {
        char	*s;
        s = getcwd(NULL, 0);
        if (!s)
        {
            perror("tsh: pwd getcwd error");
            exit(1);
        }
        else
            printf("%s\n", s);
        free(s);
        exit(0);
    }
    else
        printf("no builtin \n"); //burası önemli else olmayınca TERM error basıyor?

}

void built_in(t_data *data)
{
    int i;

    i = -1;

    while (data->nodes[++i].cmd != NULL)
    {
        is_builtin(data->nodes[i].cmd, data);
    }
}

