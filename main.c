#include "minishell.h"

int main() 
{
    t_data data;

    while (1) 
    {
        if (ft_readline(&data))
        {
            built_in(&data);
            executor(&data);
            //data_free(&data);
        }    
    }
    return 0;
}