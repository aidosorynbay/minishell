#include "minishell.h"

t_env *g_env = NULL;


void add_env_node(t_env **env_list, char *key, char *value)
{
    t_env *tmp;
    t_env *new_node;
    
    tmp = *env_list;
    while (tmp)
    {
        if (ft_strcmp(tmp->key, key) == 0)
        {
            free(tmp->value);
            tmp->value = ft_strdup(value);
            return ;
        }
        tmp = tmp->next;
    }
    new_node = malloc(sizeof(t_env));
    new_node->key = ft_strdup(key);
    new_node->value = ft_strdup(value);
    new_node->next = *env_list;
    *env_list = new_node;
}


t_env *env_init(char **envp)
{
    t_env *head;
    int i;
    char **splits;
    
    head = NULL;
    i = 0;
    while (envp[i])
    {
        splits = ft_split(envp[i], '='); // Split "KEY=VALUE"
        add_env_node(&head, splits[0], splits[1]); // Add to list
        free(splits);
        i++;
    }
    return head;
}
