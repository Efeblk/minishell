#include "minishell.h"

int main() 
{
    t_data data;
    
    while (1) 
    {
        ft_readline(&data);
        executor(data);
    }
    return 0;
}