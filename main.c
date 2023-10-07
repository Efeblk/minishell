#include "minishell.h"

int main(int argc, char *argv[], char *envp[])
{
	(void)argc;
	(void)argv;
	t_env		*env;
	t_export	*exp_list;
	t_globals	globals;
	t_data		*data;
	t_index		index;

    printf("new shell \n");
	env = load_environment(envp);
	globals.user =  get_env_val("USER", env);
	exp_list = load_export(envp);
	while (1)
	{
		data = malloc(sizeof(t_data));
		if (ft_readline(data, &globals, &env, &index))
		{
			built_in(data, &env, &exp_list);
			executor(data, &env);
			data_free(data);
		}
	}
	free_env_list(env);
	free_export_list(exp_list);
	return (0);
}
