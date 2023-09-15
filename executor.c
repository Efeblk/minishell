#include "minishell.h"

void executor(t_data data)
{
    //printf("%s\n %s",node->args[0], node->args[1]);
    execve(data.nodes->args[0], data.nodes->args, NULL);
}

int main(int argc, char const *argv[])
{
    t_data data;

    data.nodes =(t_node *)malloc(sizeof(t_node) * 2);
    data.nodes[0].cmd = (char *)malloc(sizeof(char) * 3);
    data.nodes[0].args = (char **)malloc(sizeof(char *) * 3);
    data.nodes[0].args[1] = (char *)malloc(sizeof(char) * 4);

    data.nodes[0].cmd = "ls";
    data.nodes[0].args[1] = "-la";
    data.nodes[0].args[2] = NULL;

    find_env(data);
    executor(data);
    //system("leaks main");
    return 0;
}


// void executor1(int fd1, int fd2, int *pipee)
// {
//     dup2(pipee[1], STDOUT_FILENO);
//     char * a[] = {"/bin/ls", "-la" , NULL};
//     execve(a[0], a, NULL);
//     close(pipee[1]);
// }

// void executor2(int fd1, int fd2, int *pipee)
// {


//     dup2(pipee[0], STDIN_FILENO);
//     char * a[] = {"/usr/bin/wc", "-c" , NULL};
//     execve(a[0], a, NULL);
// }

// int main(int argc, char const *argv[], char **env)
// {
//     int pipee[2];
//     pipe(pipee);
//     int pdchild1;
//     int pdchild2;
//     int status;
//     int fd1;
//     int fd2;
//     find_env("ls");
//     fd1 = open("girdi.c", O_WRONLY | O_CREAT | O_TRUNC, 0666);
//     fd2 = open("cikti.c", O_WRONLY | O_CREAT | O_TRUNC, 0666);
//     pdchild1 = fork();
//     if(pdchild1 == 0)
//         executor1(fd1 ,fd2, pipee);
//     waitpid (pdchild1, &status, WNOHANG | WUNTRACED);
//     if(pdchild1!=0)
//     {
//         pdchild2 = fork();
//         if(pdchild2 == 0)
//         {
//             executor2(fd1 ,fd2, pipee);
//             printf("******");
//         }
//     }
//     return 0;
//}
