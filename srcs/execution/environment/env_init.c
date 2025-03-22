/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorynbay <@student.42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 00:52:24 by aorynbay          #+#    #+#             */
/*   Updated: 2025/03/22 12:31:50 by aorynbay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// t_env *g_env = NULL;

static t_env	*create_env_node(char *key, char *value)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (new == NULL)
		return (NULL);
	new->key = strdup(key);
	if (value != NULL)
		new->value = strdup(value);
	else
		new->value = strdup("");
	new->next = NULL;
	return (new);
}

void	add_env_node(t_env **head, char *key, char *value)
{
	t_env	*new;
	t_env	*temp;

	if (key == NULL)
		return ;
	new = create_env_node(key, value);
	if (*head == NULL)
	{
		*head = new;
		return ;
	}
	temp = *head;
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = new;
}

t_env	*env_init(char **envp)
{
	t_env	*head;
	int		i;
	char	**splits;

	head = NULL;
	i = 0;
	while (envp[i] != NULL)
	{
		splits = ft_split(envp[i], '='); // Split "KEY=VALUE"
		if (splits != NULL && splits[0] != NULL)
		{
			if (splits[1] != NULL)
				add_env_node(&head, splits[0], splits[1]);
			else
				add_env_node(&head, splits[0], "");
			free(splits);
		}
		i++;
	}
	return (head);
}
