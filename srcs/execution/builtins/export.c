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

static void	add_to_env_lists(t_env_data *env_list, char *key, char *value)
{
	if (value)
	{
		add_env_node(&env_list->env_list, key, value, 1);
		add_env_node(&env_list->env_export_list, key, value, 1);
	}
	else
	{
		add_env_node(&env_list->env_list, key, "", 1);
		add_env_node(&env_list->env_export_list, key, "", 1);
	}
}

static void	print_exported_variables(t_env *env_export_list)
{
	t_env	*tmp;

	tmp = env_export_list;
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
}

static void	print_error(char *args, int *e_code)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(args, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	*e_code = 1;
}

static void	process_export_argument(t_env_data *env_list, char *arg,
		int *e_code)
{
	char	**split;

	split = ft_split(arg, '=');
	if (!split || !split[0] || !is_valid_identifier(split[0]))
	{
		print_error(arg, e_code);
	}
	else if (ft_strchr(arg, '='))
	{
		if (split[1])
			add_to_env_lists(env_list, split[0], split[1]);
		else
			add_to_env_lists(env_list, split[0], NULL);
	}
	else
	{
		if (!get_env_value(env_list->env_export_list, split[0]))
			add_env_node(&env_list->env_export_list, split[0], NULL, 0);
	}
	free_args(split);
}

int	ft_export(t_env_data *env_list, char **args)
{
	int	i;
	int	e_code;

	e_code = 0;
	if (!args || !args[0])
		return (perror("minishell: export: not a valid identifier"), (1));
	if (!args[1])
		return (print_exported_variables(env_list->env_export_list), (e_code));
	i = 1;
	while (args[i])
	{
		process_export_argument(env_list, args[i], &e_code);
		i++;
	}
	return (e_code);
}
