#include "minishell.h"


void ft_env(t_env_data *ev)
{
    int i;
    
    i  = 0;
    if (!ev || !ev->envp)
    {
        perror("minishell: env: No environment variables found\n");
        return;
    }
    while(ev->envp[i])
    {
        ft_putendl_fd(ev->envp[i], 1);
        i++;
    }
    return ;
}