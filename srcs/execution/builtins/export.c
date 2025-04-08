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

void	ft_export(t_env_data *env_list, char **args)
{
	int		i;
	char	**split;
	t_env	*tmp;

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
		return ;
	}
	i = 1;
	while (args[i])
	{
		split = ft_split(args[i], '=');
		if (!split || !split[0])
		{
			perror("minishell: export: not a valid identifier");
			free(split);
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
}





