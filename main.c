#include "minishell.h"

int main(int argc, char *argv[], char *envp[]) 
{
    (void)argc;
    (void)argv;

    t_env *env;
    t_export *exp_list;
    t_globals globals;


    globals.status = 0;
    env = load_environment(envp);
    globals.user = getenv("USER"); //get_env_val("USER", env);
    exp_list = load_export(envp);
    while (1) 
    {
		t_data *data;
        data = malloc(sizeof(t_data));
        if (ft_readline(data, &globals))
        {
            built_in(data, &globals, &env, &exp_list);
            //executor(data, &globals, envp);
            data_free(data);   
            //print_node(data);
        }    
    }
    free_env_list(env);
    free_export_list(exp_list);
    return 0;
}
