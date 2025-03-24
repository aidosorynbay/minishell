/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorynbay <@student.42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 00:52:24 by aorynbay          #+#    #+#             */
/*   Updated: 2025/03/24 14:04:11 by aorynbay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// t_env *g_env = NULL;


static t_env *create_env_node(char *key, char *value)
{
	t_env *new;

	new = malloc(sizeof(t_env));
	if (new == NULL)
		return (NULL);
	new->key = strdup(key);
	if (new->key == NULL)
	{
		free(new);
		return (NULL);
	}
	if (value != NULL)
		new->value = strdup(value);
	else
		new->value = strdup("");

	if (new->value == NULL)
	{
		free(new->key);
		free(new);
		return (NULL);
	}
	new->next = NULL;
	return (new);
}

void	add_env_node(t_env **head, char *key, char *value)
{
	t_env	*new;
	t_env	*temp;

	if (!key || !head)
		return ;
	new = create_env_node(key, value);
	if (!new)
		return ;
	if (!*head)
	{
		*head = new;
		return ;
	}
	temp = *head;
	while (temp->next)
	{
		if (strcmp(temp->key, key) == 0) // Prevent duplicate keys
		{
			free(temp->value);
			temp->value = strdup(value);
			free(new);
			return ;
		}
		temp = temp->next;
	}
	temp->next = new;
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
					add_env_node(&env_data->env_list, splits[0], splits[1]);
					add_env_node(&env_data->env_export_list, splits[0], splits[1]);
				}
				else
				{
					add_env_node(&env_data->env_list, splits[0], "");
					add_env_node(&env_data->env_export_list, splits[0], "");
				}
			}
			free(splits);
		}
		i++;
	}
	return (env_data);
}
