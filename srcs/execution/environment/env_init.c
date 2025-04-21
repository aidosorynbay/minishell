/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorynbay <@student.42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 00:52:24 by aorynbay          #+#    #+#             */
/*   Updated: 2025/04/18 13:25:24 by aorynbay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	assign_key(char *key, t_env *current, char *value, int has_value)
{
	if (current == NULL)
		return ;
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
}

void	add_env_node(t_env **env_list, char *key, char *value, int has_value)
{
	t_env	*new;
	t_env	*current;

	current = *env_list;
	assign_key(key, current, value, has_value);
	new = malloc(sizeof(t_env));
	if (!new)
		return ;
	new->key = ft_strdup(key);
	if (value)
		new->value = ft_strdup(value);
	else
		new->value = NULL;
	new->has_value = has_value;
	new->next = *env_list;
	*env_list = new;
}

static void	add_env_variables(t_env_data *env_data, char **splits)
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
}

t_env_data	*env_init(char **envp)
{
	t_env_data	*env_data;
	char		**splits;
	int			i[2];

	env_data = malloc(sizeof(t_env_data));
	if (env_data == NULL)
		return (NULL);
	env_data->env_list = NULL;
	env_data->env_export_list = NULL;
	env_data->last_exit = 0;
	i[0] = 0;
	while (envp[i[0]] != NULL)
	{
		splits = ft_split(envp[i[0]], '=');
		if (splits != NULL)
		{
			add_env_variables(env_data, splits);
			i[1] = 0;
			while (splits[i[1]] != NULL)
				free(splits[i[1]++]);
			free(splits);
		}
		i[0]++;
	}
	return (env_data);
}
