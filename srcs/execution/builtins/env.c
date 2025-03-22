#include "minishell.h"


// void ft_env(t_env_data *ev)
// {
//     t_env *tmp;

//     tmp = ev->env_list;
//     if (!ev || !ev->env_list)
//     {
//         perror("minishell: env: No environment variables found\n");
//         return;
//     }
//     while(tmp)
//     {
//         ft_putstr_fd(tmp->key, 1);
//         ft_putstr_fd("=", 1);
//         ft_putstr_fd(tmp->value, 1);
//         ft_putstr_fd("\n", 1);
//         tmp = tmp->next;
//     }
//     return ;
// }

void ft_env(t_env *env_list)
{
    t_env *tmp;

    if (!env_list)
        return;

    tmp = env_list;
    while (tmp)
    {
        if (tmp->value)  // ✅ Print only variables with values
        {
            ft_putstr_fd(tmp->key, 1);
            ft_putstr_fd("=", 1);
            ft_putstr_fd(tmp->value, 1);
            ft_putstr_fd("\n", 1);
        }
        fprintf(stderr, "----------------------------\n");
        fprintf(stderr, "tmp->key: %s\n", tmp->key);
        tmp = tmp->next;
        fprintf(stderr, "----------------------------\n");
    }
}

