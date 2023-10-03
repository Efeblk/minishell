#include "minishell.h"

int main(int argc, char *argv[], char *envp[]) 
{
    (void)argc;
    (void)argv;
    t_env *env;
    
    printf("ilk min, \n");
    t_globals globals;
    globals.status = 0;
    env = load_environment(envp);
    if (!env)
    {
        printf("elmacık \n");
    }
    globals.user = get_env_val("USER", env);
    
    printf(" \n HEHEEEY %s \n", globals.user);
    while (1) 
    {
		t_data *data;
        data = malloc(sizeof(t_data));
        if (ft_readline(data, &globals))
        {
            built_in(data, &globals);
            executor(data, &globals);
            data_free(data);   
            //print_node(data);
        }     
    }
    
    return 0;
}
