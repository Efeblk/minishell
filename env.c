#include "minishell.h"

int env_count(char **envp)
{
    int i;

    i = 0;
    while (envp[i] != NULL)
        i++;
    return (i);
}

char *env_list(char **envp, t_env *env)
{
    int i;

    i = 0;
    while (envp[i])
    {
        env->key = strtok(envp[i], "=");
        env->value = strtok(NULL, "=");
        env->full = envp[i];
        i++;
    }
    return (env->full);
}
