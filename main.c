#include "minishell.h"

int main() 
{
    while (1) 
    {
        t_data *data;
        data = malloc(sizeof(t_data));
        if (ft_readline(data))
        {
            //built_in(data);
            executor(data);
            data_free(data);   
            //system("leaks minishell");       //
        }     
    }
    
    return 0;
}