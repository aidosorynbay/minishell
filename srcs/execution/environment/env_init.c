/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorynbay <@student.42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 00:52:24 by aorynbay          #+#    #+#             */
/*   Updated: 2025/04/08 21:33:17 by aorynbay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_env_node(t_env **env_list, char *key, char *value, int has_value)
{
	t_env	*new;
	t_env	*current;

	current = *env_list;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			if (value)
			{
				free(current->value);
				current->value = ft_strdup(value);
			}
			current->has_value = has_value;
			return ;
		}
		current = current->next;
	}
	new = malloc(sizeof(t_env));
	if (!new)
		return ;
	new->key = ft_strdup(key);
	new->value = value ? ft_strdup(value) : NULL;
	new->has_value = has_value;
	new->next = *env_list;
	*env_list = new;
}

t_env_data *env_init(char **envp)
{
	t_env_data *env_data;
	int i;
	char **splits;

	env_data = malloc(sizeof(t_env_data));
	if (env_data == NULL)
		return (NULL);
	env_data->env_list = NULL;
	env_data->env_export_list = NULL;
	env_data->last_exit = 0;
	i = 0;
	while (envp[i] != NULL)
	{
		splits = ft_split(envp[i], '='); // Split "KEY=VALUE"
		if (splits != NULL)
		{
			if (splits[0] != NULL)
			{
				if (splits[1] != NULL)
				{
					add_env_node(&env_data->env_list, splits[0], splits[1], 1);
					add_env_node(&env_data->env_export_list, splits[0], splits[1], 1);
				}
				else
				{
					add_env_node(&env_data->env_list, splits[0], "", 1);
					add_env_node(&env_data->env_export_list, splits[0], "", 1);
				}
			}
			free(splits);
		}
		i++;
	}
	return (env_data);
}
