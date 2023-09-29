#include "minishell.h"

int main() 
{
    while (1) 
    {
        t_data *data;
        data = malloc(sizeof(t_data));
        if (ft_readline(data))
        {
            //free(data->nodes[0].cmd);
            //free(data->nodes[1].cmd);
            data_free(data);
            free(data);
            break;
            //executor(&data);
        }    
    }
    system("leaks minishell");
    return 0;
}