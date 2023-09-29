#include "minishell.h"

int main() 
{
    while (1) 
    {
        t_data *data;
        data = malloc(sizeof(t_data));
        if (ft_readline(data))
        {
<<<<<<< HEAD
            //built_in(data);
            //free(data->nodes[0].cmd);
            //free(data->nodes[1].cmd);
            executor(data);
            //data_free(data);
            free(data);     
            //system("leaks minishell");       //
        }    
    }
    
=======
            executor(data);
            //free(data->nodes[1].cmd);
            //free(data->nodes[1].args);

            // //free(data->nodes[1].cmd);
            //data_free(data);
            free(data->nodes[0].cmd);
            free(data->nodes[0].args[0]);
            free(data->nodes[0].args[1]);
            free(data->nodes[0].args);
            free(data->nodes[0].infile);
            free(data->nodes[0].outfile);
            free(data->nodes[0].operators);
            // //free(data->nodes[1].cmd);
            free(data->nodes);
            free(data);
            system("leaks minishell");


            //break;
            
        }    
    }
>>>>>>> ed1ead81774cabb62e559dd07ec1e66fa56d7861
    return 0;
}