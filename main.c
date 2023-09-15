#include "minishell.h"

int main(int argc, char const *argv[])
{
    t_data *data;
    t_node *node;
    data = (t_data *)malloc(sizeof(t_data));
    node = (t_node *)malloc(sizeof(t_node));
    node = (char *)malloc(sizeof(char) * 3);
    node.args = (char **)malloc(sizeof(char *) * 3);
    node.args[1] = (char *)malloc(sizeof(char) * 4);
    node.args[2] = NULL;
    node.cmd = "ls";
    node.args[1] = "-la";
    data->nodes = (t_node *)malloc(sizeof(t_node));
    data->nodes[0] = node;
    find_env(node);
    executor(node);
    //system("leaks main");
    return 0;
}