#include "minishell.h"

int ft_echo(char **args)
{
    if (strcmp(args[1], "-n") == 0)
    {
        int i = 2;
        while (args[i] != NULL)
        {
            ft_putstr_fd(args[i], 1);
            if (args[i + 1])
                write(1, " ", 1);
            i++;
        }
    }
    else
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
    }
    return (1);
}
