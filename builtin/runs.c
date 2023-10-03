#include "minishell.h"

/*void	run_cd(t_data *data)
{
    char	*s;

	if (node.arg_count != 1 && node.args[1][0] != '~')
	{
		if (chdir(node.args[1]) != 0)
		{
			printf("tsh: cd: %s: No such file or directory\n", node.args[1]);
			question_mark_update(ft_strdup("?=1"), -1);
		}
	}
	else
	{
		s = getenv("HOME");
		if (s && *s)
		{
			if (chdir(s))
			{
				perror("tsh: cd chdir error");
				question_mark_update(ft_strdup("?=1"), -1);
			}
		}
	}*/

void run_cd(t_data *data, int i)
{
	if (data->nodes[i].args[1])
	{
		chdir(data->nodes[i].args[1]);
	}
	else
	{
		chdir(getenv("HOME"));
	}
}

char *return_pwd(void)
{
	return(getcwd(NULL, 0));
}

void run_pwd(void)
{
    char	*s;
    s = getcwd(NULL, 0);
    if (!s)
    {
        perror("tsh: pwd getcwd error");
        exit(1);
    }
    else
        printf("%s\n", s);
    free(s);
}

void run_exit(t_data *data)
{
    data_free(data); 
    printf("exit");
    exit(0);
}

void run_echo(t_data *data, int i)
{
	int j;

	j = 1;

	while (data->nodes[i].args[j] != NULL)
			j++;
	j--;
	if (data->nodes[i].args[j])
	{
		if (data->nodes[i].args[1][0] == '-' && data->nodes[i].args[1][1] == 'n')
		{
			if (data->nodes[i].args[j][0] == '-' && data->nodes[i].args[j][1] == 'n' && data->nodes[i].args[j][2] == '\0')
			{
			}
			else
				printf("%s", data->nodes[i].args[j]);
		}
		else
			printf("%s\n", data->nodes[i].args[j]);
	}
}