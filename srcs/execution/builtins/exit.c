#include "minishell.h"

int ft_exit(char **args)
{
    if (args[1])
    {
        int exit_code = ft_atoi(args[1]);
        exit(exit_code);
    }
    exit(0);
    return 1;
}