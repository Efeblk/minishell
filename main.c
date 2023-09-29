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
            //free(data->nodes[0].cmd);
            //free(data->nodes[1].cmd);
            executor(data);
            //data_free(data);
            free(data);     
            //system("leaks minishell");       //
        }    
    }
    
    return 0;
}