#include "minishell.h"

// void add_env_node(t_env **env_list, char *key, char *value, int flag)
// {
//     t_env *tmp = *env_list;
//     t_env *new_node;

//     if (!key)
//         return;
//     while (tmp)
//     {
//         if (ft_strcmp(tmp->key, key) == 0)
//         {
//             free(tmp->value);
//             if (value)
//                 tmp->value = ft_strdup(value);
//             else
//                 tmp->value = ft_strdup("");
//             return;
//         }
//         tmp = tmp->next;
//     }

//     new_node = malloc(sizeof(t_env));
//     if (!new_node)
//         return;

//     new_node->key = ft_strdup(key);
//     if (value)
//         new_node->value = ft_strdup(value);
//     else
//         new_node->value = ft_strdup("");

//     new_node->next = *env_list;
//     *env_list = new_node;
// }

// t_env *env_init(char **envp)
// {
//     t_env *head;
//     int i;
//     char **splits;
//     int j;
    
//     head = NULL;
//     i = 0;
//     while (envp[i])
//     {
//         splits = ft_split(envp[i], '=');
//         if (!splits)
//             return NULL;
//         add_env_node(&head, splits[0], splits[1]);
//         j = 0;
//         while (splits[j])
//             free(splits[j++]);
//         free(splits);
//         i++;
//     }
//     return head;
// }

int add_env_node(t_env **list, char *key, char *value)
{
    t_env *tmp;
    t_env *new_node;

    if (!key)  // ✅ Prevent NULL key issues
        return (0);

    // ✅ Check if the variable already exists and update it
    tmp = *list;
    while (tmp)
    {
        if (ft_strcmp(tmp->key, key) == 0)
        {
            free(tmp->value);
            if (value)
                tmp->value = ft_strdup(value);
            else
                tmp->value = ft_strdup("");
            return (1);
        }
        tmp = tmp->next;
    }

    // ✅ If not found, create a new node
    new_node = malloc(sizeof(t_env));
    if (!new_node)
        return (0);

    new_node->key = ft_strdup(key);
    if (value)
        new_node->value = ft_strdup(value);
    else
        new_node->value = ft_strdup("");

    new_node->next = *list;
    *list = new_node;

    return (1);  // ✅ Return 1 to indicate success
}

t_env_data *env_init(char **envp)
{
    t_env_data *data;
    int i;
    char **split;
    int j;

    data = malloc(sizeof(t_env_data));  // ✅ Allocate memory for both lists
    if (!data)
        return NULL;

    data->env_list = NULL;
    data->export_list = NULL;
    i = 0;
    
    while (envp[i])
    {
        split = ft_split(envp[i], '=');
        if (!split)
            return NULL;

        if (split[0])  // ✅ Ensure key exists
        {
            if (split[1])
            {
                add_env_node(&data->env_list, split[0], split[1]);  // ✅ Store in `env`
                add_env_node(&data->export_list, split[0], split[1]);  // ✅ Store in `export`
            }
            else
            {
                add_env_node(&data->export_list, split[0], "");  // ✅ Only store in `export`
            }
        }

        j = 0;
        while (split[j])
            free(split[j++]);
        free(split);
        i++;
    }
    return data;
}
