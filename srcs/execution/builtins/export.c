#include "minishell.h"

void ft_export(t_env_data *env_list, char **args)
{
    int i;
    char **split;
    t_env *env;
    t_env *tmp;

    fprintf(stderr, "---------------*************----------------\n");
    fprintf(stderr, "Executing builtin command: export\n");

    // If no arguments, print environment variables
    if (!args[1])
    {
        tmp = env_list->env_list;
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
        return;
    }

    // Process each argument (`export VAR=value`)
    i = 1;
    env = env_list->env_list;
    while (args[i])
    {
        // Split into "VAR" and "VALUE"
        split = ft_split(args[i], '=');
        if (!split[0]) // Invalid format
        {
            ft_putstr_fd("minishell: export: `", 2);
            ft_putstr_fd(args[i], 2);
            ft_putstr_fd("': not a valid identifier\n", 2);
            if (split)
                free(split);
            i++;
            continue;
        }
        // If `VAR=value`, store value
        if (split[1])
            add_env_node(&env, split[0], split[1]);
        else
            add_env_node(&env, split[0], ""); // If only `VAR`, store empty value
        free(split);
        i++;
    }
}
