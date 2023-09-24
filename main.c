#include "minishell.h"

int main() 
{
    t_data data;
    //char *a[] = { "/bin/ls", "la |", NULL};
    //execve(a[0], a, NULL);
    while (1) 
    {
        ft_readline(&data);
        executor(data);
    }
    return 0;
}