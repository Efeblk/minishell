#include "minishell.h"

int env_count(char **envp)
{
    int i;

    i = 0;
    while (envp[i] != NULL)
        i++;
    return (i);
}

char **env_list(char **envp, t_env *env)
{
    int       i;
    char    **list;

    i = 0;
    list = (char **) malloc(sizeof(char *) * (env_count(envp)) + 1);
    while (envp[i])
    {
        list[i] = envp[i];
        i++;
    }
    list[i] = 0;
    env->env_list = list;
    return (env->env_list);
}

char    **add_env_list(t_env *env, char *str)
{
    int i;
    int j;
    char **new_list;

    i = 0;
    j = 0;
    new_list = (char **) malloc(sizeof(char *) * env_count(env->env_list) + 1);
    while (env->env_list[i])
        i++;
    while (str[j])
    {
        env->env_list[i] = &str[j];
        j++;
    }
    env->env_list = new_list;
    return (new_list);
}


int main(int ac, char **av, char **envp)
{
   t_env env;
   int i;
   char **a;
   char **b;

   i = 0;
   a = env_list(envp, &env);
   while (i < env_count(envp))
   {
        printf("%s\n", a[i]);
        i++;
   }
   i = 0;
   b = add_env_list(&env, "a=5");
   while (env.env_list[i])
   {
        printf("**%s**\n", env.env_list[i]);
        i++;
   }
   return (0);
}
