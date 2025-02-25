#include "minishell.h"

void ft_export(t_env_data *env_list, char **args)
{
    int i;

    if (!args[1])
    {
        t_env *tmp = env_list->env;
        while (tmp)
        {
            ft_putstr_fd("declare -x ", 1);
            ft_putstr_fd(tmp->key, 1);
            if (tmp->value)
            {
                ft_putstr_fd("=\"", 1);
                ft_putstr_fd(tmp->value, 1);
                ft_putstr_fd("\"", 1);
            }
            ft_putstr_fd("\n", 1);
            tmp = tmp->next;
        }
        return ;
    }
    i = 1;
    t_env *env = env_list->env;
    while (args[i])
    {
        char **split = ft_split(args[i], '=');
        if (!split[0])
            perror("minishell: export: not a valid identifier\n");
        if (split[1])
            add_env_node(&env, split[0], split[1]);
        else
            add_env_node(&env, split[0], "");
        free(split);
        i++;
    }
    return ;
}
