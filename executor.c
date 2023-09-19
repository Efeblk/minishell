#include "minishell.h"

int **pipe_create(int pipe_count)
{
    int i;
    int **pipes;

    i = -1;

    if (pipe_count == 0)
    {
        pipes = (int **)malloc(sizeof(int *) * 2);
        pipes[0] = NULL;
        pipes[1] = NULL;
        return pipes;
    }

    pipes = (int **)malloc(sizeof(int *) * (pipe_count + 1));
    while (++i < pipe_count)
    {
        pipes[i] = (int *)malloc(sizeof(int) * 2);
        if(pipe(pipes[i]) == -1)
        {
            printf("pipe error \n");
        }
    }
    pipes[i] = NULL;
    return (pipes);
}

void router(t_data data, int i, int *fd, int *fd2)
{
    // printf("process %i \n", i);
    // if (i >= 1)
    // {
    //     char asd[5];
    //     ssize_t bytesRead = read(fd[0], asd, sizeof(asd) - 1);
    //     asd[bytesRead] = '\0'; // Null-terminate the string
    //     printf("Child Process Received: %s -- %i\n", asd, i);
    // }
    printf("%s - -- -- - - - %s\n", data.nodes[i].args[0],data.nodes[i].args[1]);
    if(i >= 1)
    {
        printf("pipe\n");
        dup2(fd[0], STDIN_FILENO);
        if (fd2 != NULL && data.tokens[i][0] == '|')
        {
            close(fd2[0]);
            dup2(fd2[1], STDOUT_FILENO);
        }
    }
    else if (data.tokens[i][0] == '|')
    {    
        printf("pipe\n");
        dup2(fd[1], STDOUT_FILENO);
    }
    if (fd != NULL)
    {
        printf("close fd\n");
        close(fd[0]);
        close(fd[1]);
    }
    if (fd2 != NULL)
    {
        printf("close fd2\n");
        close(fd2[0]);
        close(fd2[1]);
    }
    printf("hey\n");
    execve(data.nodes[i].args[0], data.nodes[i].args, NULL);
}

int executor(t_data data)
{
    if((find_env(data)) == -1)
        return -1;

    int **pipes;
    pipes = pipe_create(data.pipe_count);
    int i = -1;
    pid_t pid;
    int status;
    while (++i < (data.pipe_count + 1))
    {
        pid = fork();
        if (pid == 0)
        {
            router(data, i, pipes[(i / 2)], pipes[(i / 2) + 1]);
            exit(0);
        }
        if (data.pipe_count > 0)
            close(pipes[(i / 2)][1]);
        
        waitpid(pid, &status, WUNTRACED);
    }
    close_pipes(pipes, data.pipe_count);
    return 0;
}

int main(int argc, char const *argv[])
{
    t_data data;

    data.nodes =(t_node *)malloc(sizeof(t_node) * 3);
    data.nodes[0].cmd = (char *)malloc(sizeof(char) * 3);
    data.nodes[0].args = (char **)malloc(sizeof(char *) * 3);
    data.nodes[0].args[1] = (char *)malloc(sizeof(char) * 4);

    data.nodes[0].cmd = "ls\0";
    data.nodes[0].args[1] = "-la\0";
    data.nodes[0].args[2] = NULL;

    
    
    //printf("size of %lu \n", ft_strlen(data.nodes[0].cmd));
    data.nodes[1].cmd = (char *)malloc(sizeof(char) * 5);
    data.nodes[1].args = (char **)malloc(sizeof(char *) * 3);
    data.nodes[1].args[1] = (char *)malloc(sizeof(char) * 4);

    data.nodes[1].cmd = "grep\0";
    data.nodes[1].args[1] = "git\0";
    data.nodes[1].args[2] = NULL;

    /////////////////////////////////////////////////////////
    data.nodes[2].cmd = (char *)malloc(sizeof(char) * 3);
    data.nodes[2].args = (char **)malloc(sizeof(char *) * 3);
    data.nodes[2].args[1] = (char *)malloc(sizeof(char) * 2);

    data.nodes[2].cmd = "wc\0";
    data.nodes[2].args[1] = "-l\0";
    data.nodes[2].args[2] = NULL;

    ////////////////////////////////////////////////////////////
    data.tokens = (char **)malloc(sizeof(char *) * 2);
    data.tokens[0] = (char *)malloc(sizeof(char) * 2);
    data.tokens[1] = (char *)malloc(sizeof(char) * 2);

    data.pipe_count = 2;

    data.tokens[1][0] = '|';
    data.tokens[1][1] = '\0';
    data.tokens[0][1] = '\0';
    data.tokens[0][0] = '|';


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
