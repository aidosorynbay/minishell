#include "minishell.h"

int ft__echo(char **args)
{
    int i = 1;
    while (args[i])
    {
        ft_putstr_fd(args[i], 1);
        if (args[i + 1])
            write(1, " ", 1);
        i++;
    }
    ft_putstr_fd("\n", 1);
    return (1);
}