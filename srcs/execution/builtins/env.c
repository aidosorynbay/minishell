#include "minishell.h"


void ft_env(t_env_data *ev)
{
    t_env *tmp;

    tmp = ev->env;
    if (!ev || !ev->env)
    {
        perror("minishell: env: No environment variables found\n");
        return;
    }
    while(tmp)
    {
        ft_putstr_fd(tmp->key, 1);
        ft_putstr_fd("=", 1);
        ft_putstr_fd(tmp->value, 1);
        ft_putstr_fd("\n", 1);
        tmp = tmp->next;
    }
    return ;
}
