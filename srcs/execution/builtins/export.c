#include "minishell.h"

void ft_export(t_env_data *env_list, char **args)
{
    int i;
    char **split;
    t_env *tmp;

    fprintf(stderr, "---------------*************----------------\n");
    fprintf(stderr, "Executing builtin command: export\n");

    // If no arguments, print environment variables
    if (!args[1])
    {
        tmp = env_list->env;
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
    i = 1;
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
            continue; // Skip this argument and continue to the next one
        }
        if (!is_valid_env_key(split[0]))
        {
            ft_putstr_fd("minishell: export: `", 2);
            ft_putstr_fd(args[i], 2);
            ft_putstr_fd("': not a valid identifier\n", 2);
            if (split)
                free(split);
            i++;
            continue; // Skip this argument and continue to the next one
        }

        if (split[1])
        {
            fprintf(stderr, "adding env node: %s=%s\n", split[0], split[1]);
            add_env_node(&(env_list->env), split[0], split[1]); // Pass address of env_list->env
        }
        else
            add_env_node(&(env_list->env), split[0], "");
        if (split)
            free(split);
        i++;
    }
}
