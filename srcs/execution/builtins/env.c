#include "minishell.h"


void ft_env(char **envp)
{
    int i;
    
    i  = 0;
    if (!envp || !envp[0])
    {
        printf("minishell: env: No environment variables found\n");
        return;
    }
    while(envp[i])
    {
        ft_putendl_fd(envp[i], 1);
        i++;
    }
    return ;
}