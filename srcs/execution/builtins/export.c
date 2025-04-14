/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorynbay <@student.42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 20:21:09 by aorynbay          #+#    #+#             */
/*   Updated: 2025/04/14 20:21:17 by aorynbay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_value(t_env *env_list, char *key)
{
	t_env	*tmp;

	tmp = env_list;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

int	is_valid_identifier(const char *str)
{
	int	i;

	if (!str || (!ft_isalpha(str[0]) && str[0] != '_'))
		return (0);
	i = 1;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	ft_export(t_env_data *env_list, char **args)
{
	int		i;
	char	**split;
	t_env	*tmp;
	int		exit_code;

	exit_code = 0;
	if (!args || !args[0])
	{
		perror("minishell: export: not a valid identifier");
		return (1);
	}
	if (!args[1])
	{
		tmp = env_list->env_export_list;
		while (tmp)
		{
			ft_putstr_fd("declare -x ", 1);
			ft_putstr_fd(tmp->key, 1);
			if (tmp->has_value)
			{
				ft_putstr_fd("=\"", 1);
				if (tmp->value)
					ft_putstr_fd(tmp->value, 1);
				ft_putstr_fd("\"", 1);
			}
			ft_putstr_fd("\n", 1);
			tmp = tmp->next;
		}
		return (exit_code);
	}
	i = 1;
	while (args[i])
	{
		split = ft_split(args[i], '=');
		if (!split || !split[0] || !is_valid_identifier(split[0]))
		{
			ft_putstr_fd("minishell: export: `", 2);
			ft_putstr_fd(args[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			free(split);
			exit_code = 1;
			i++;
			continue;
		}
		if (ft_strchr(args[i], '='))
		{
			if (split[1])
			{
				add_env_node(&env_list->env_list, split[0], split[1], 1);
				add_env_node(&env_list->env_export_list, split[0], split[1], 1);
			}
			else
			{
				add_env_node(&env_list->env_list, split[0], "", 1);
				add_env_node(&env_list->env_export_list, split[0], "", 1);
			}
		}
		else
		{
			if (!get_env_value(env_list->env_export_list, split[0]))
				add_env_node(&env_list->env_export_list, split[0], NULL, 0);
		}
		free(split);
		i++;
	}
	return (exit_code);
}





