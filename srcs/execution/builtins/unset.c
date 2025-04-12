/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorynbay <@student.42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 08:20:31 by aorynbay          #+#    #+#             */
/*   Updated: 2025/04/10 08:20:31 by aorynbay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	remove_env_node(t_env **env_list, char *key)
{
	t_env	*prev;
	t_env	*curr;

	curr = *env_list;
	prev = NULL;
	while (curr)
	{
		if (ft_strcmp(curr->key, key) == 0)
		{
			if (prev)
				prev->next = curr->next;
			else
				*env_list = curr->next;
			free(curr->key);
			if (curr->value)
				free(curr->value);
			free(curr);
			return ;
		}
		prev = curr;
		curr = curr->next;
	}
}

int	ft_unset(t_env_data *env_list, char **args)
{
	int	i;

	i = 1;
	while (args[i])
	{
		remove_env_node(&env_list->env_list, args[i]);
		remove_env_node(&env_list->env_export_list, args[i]);
		i++;
	}
	return (0);
}
