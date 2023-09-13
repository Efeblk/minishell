#include "minishell.h"

void find_env(char *cmd)
{
    char *env;
    char **bin;
    int i;
    char *tmp;
    char *ls = "ls";
    env = getenv("PATH");
    printf("%s\n", getenv("PATH"));
    bin = ft_split(env, ':');

    printf("%s", bin[0]);
    i = 0;
    while (bin[i])
    {
        bin[i][ft_strlen(bin[i])] = '/';
        tmp = ft_strjoin(bin[i], ls);
        printf("%i",access(tmp, F_OK | X_OK));
        printf("%s\n", tmp);
        i++;
    }
}

void executor1(int fd1, int fd2, int *pipee)
{
    dup2(pipee[1], STDOUT_FILENO);
    char * a[] = {"/bin/ls", "-la" , NULL};
    execve(a[0], a, NULL);
    close(pipee[1]);
}

void executor2(int fd1, int fd2, int *pipee)
{


    dup2(pipee[0], STDIN_FILENO);
    char * a[] = {"/usr/bin/wc", "-c" , NULL};
    execve(a[0], a, NULL);
}

int main(int argc, char const *argv[], char **env)
{
    int pipee[2];
    pipe(pipee);
    int pdchild1;
    int pdchild2;
    int status;
    int fd1;
    int fd2;
    find_env();
    fd1 = open("girdi.c", O_WRONLY | O_CREAT | O_TRUNC, 0666);
    fd2 = open("cikti.c", O_WRONLY | O_CREAT | O_TRUNC, 0666);
    pdchild1 = fork();
    if(pdchild1 == 0)
        executor1(fd1 ,fd2, pipee);
    waitpid (pdchild1, &status, WNOHANG | WUNTRACED);
    if(pdchild1!=0)
    {
        pdchild2 = fork();
        if(pdchild2 == 0)
        {
            executor2(fd1 ,fd2, pipee);
            printf("******");
        }
    }
    return 0;
}
