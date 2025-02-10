#include "minishell.h"
//incomplete ; fix the other cds too

int ft_cd(char **args)
{
    if (!args[1])
    {
        chdir(getenv("HOME"));
        return 1;
    }
    else if (chdir(args[1]) == -1)
    {
        perror("cd");
        return 0;
    }
    return 1;
}
