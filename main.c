#include "minishell.h"

 int main(int argc, char *argv[], char *envp[]) 
 {
	(void)argv;
	(void)argc;
	
	t_env *env;

    
	env = load_environment(envp);
    while (1) 
    {
		t_data *data;
        data = malloc(sizeof(t_data));
        if (ft_readline(data))
        {
            built_in(data, envp, env);
            //executor(data);
            data_free(data);  
            //print_node(data);
            //system("leaks minishell");       //
        } 
    }
    
    return 0;
 }

// int main(int argc, char *argv[], char *envp[])
// {
//     (void)argv;
//     (void)argc;
// 	t_env *env_list = load_environment(envp);

// 	printf("Original environment variables:\n");
// 	print_list(env_list);

// 	// Add a new variable
// 	add_env_node(&env_list, "NEW_VARIABLE", "new_value");
// 	printf("\nAfter adding NEW_VARIABLE:\n");
// 	print_list(env_list);

// 	// Update an existing variable
// 	update_env_node(env_list, "PATH", "/new/path");
// 	printf("\nAfter updating PATH:\n");
// 	print_list(env_list);

// 	// Delete a variable
// 	delete_env_node (&env_list, "NEW_VARIABLE");
// 	printf("\nAfter deleting NEW_VARIABLE:\n");
// 	print_list(env_list);

// 	free_env_list(env_list);
// 	return 0;
// }