#include "minishell.h"

void add_env_node(t_env **env_list, char *key, char *value)
{
    t_env *tmp = *env_list;
    t_env *new_node;

    if (!key)
        return;
    while (tmp)
    {
        if (ft_strcmp(tmp->key, key) == 0)
        {
            free(tmp->value);
            if (value)
                tmp->value = ft_strdup(value);
            else
                tmp->value = ft_strdup("");
            return;
        }
        tmp = tmp->next;
    }

    new_node = malloc(sizeof(t_env));
    if (!new_node)
        return;

    new_node->key = ft_strdup(key);
    if (value)
        new_node->value = ft_strdup(value);
    else
        new_node->value = ft_strdup("");

    new_node->next = *env_list;
    *env_list = new_node;
}

t_env *env_init(char **envp)
{
    t_env *head;
    int i;
    char **splits;
    int j;
    
    head = NULL;
    i = 0;
    while (envp[i])
    {
        splits = ft_split(envp[i], '=');
        if (!splits)
            return NULL;
        add_env_node(&head, splits[0], splits[1]);
        j = 0;
        while (splits[j])
            free(splits[j++]);
        free(splits);
        i++;
    }
    return head;
}

