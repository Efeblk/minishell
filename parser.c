#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *quote_separator(char *str)
{
    int i;
    int j; 
    int quote_count;
    char    *temp;

    i = -1;
    j = 0;
    quote_count = quote_counter(str);
    if (quote_count % 2)
    {
        printf("Error! Quote count must be even!\n");
        exit(1);
    }
    if (!ft_strchr(str, '|'))
    {
        temp = (char *)malloc(ft_strlen(str) + 1); 
        if (temp == NULL)
        {
            printf("Memory allocation error!");
            return (NULL);
        }
        i = -1;
        while (str[++i])
        {
            if (str[i] != '"' && str[i] != '\'')
            {
                temp[j] = str[i];
                j++;
            }
        }
        temp[j] = '\0'; 
        free(str);
        return (temp);   
    }
    else if (ft_strchr(str, '|'))
    {
        printf("Tırnak içinde pipe\n");
        exit(1);
    }
    else
        return (str);
}

void    space_separator(char *input)
{
    char    **str;
    int         i;

    i = 0;
    str = ft_split(input, ' ');
    while (str[i])
    {
        if (ft_strchr(str[i], '"') || ft_strchr(str[i], '\''))
            str[i] = quote_separator(str[i]);
        else if ((ft_strchr(str[i], '<')) || (ft_strchr(str[i], '>'))
            str[i] = redirection_separator(str[i]);
        i++;
    }
    i = 0;
    while (str[i])
    {
        printf("str[%d]:%s\n", i, str[i]);
        i++;
    }
}


void    ft_readline(t_data *data)
{
    (void)data;
    char    *input;
    int     i;

    i = 0;
    input = readline("Enter a command: ");
    add_history(input);
    space_separator(input);
    free(input);
}

int main() 
{
    t_data data;

    while (1)
    {
        ft_readline(&data);
    }
    return (0);
}