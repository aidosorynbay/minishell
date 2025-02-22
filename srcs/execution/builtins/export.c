#include "minishell.h"

void ft_export(t_env **env_list, char **args)
{
    if (!args[1]) // Case: `export` with no arguments (print env)
    {
        t_env *tmp = *env_list;
        while (tmp)
        {
            printf("declare -x %s=\"%s\"\n", tmp->key, tmp->value);
            tmp = tmp->next;
        }
        return;
    }

    int i = 1;
    while (args[i])
    {
        char **split = ft_split(args[i], '='); // Split into key=value
        if (!split[0]) // Invalid format
            perror("minishell: export: not a valid identifier\n");
        if (split[1]) // Case: key=value
            add_env_node(&g_env, split[0], split[1]);
        else
            add_env_node(&g_env, split[0], "");
        free(split);
        i++;
    }
}
