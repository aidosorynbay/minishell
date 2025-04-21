/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorynbay <@student.42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 20:45:38 by aorynbay          #+#    #+#             */
/*   Updated: 2025/03/03 20:45:38 by aorynbay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_arg(t_env *tmp)
{
	int	count;

	count = 0;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	return (count);
}

char	*get_next_path(char *path, int *index)
{
	int		start;
	int		len;
	char	*token;

	while (path[*index] == ':')
		(*index)++;
	if (path[*index] == '\0')
		return (NULL);
	start = *index;
	len = find_char(path + start, ":");
	*index += len;
	token = malloc(len + 1);
	if (!token)
		return (NULL);
	ft_strncpy(token, path + start, len);
	token[len] = '\0';
	return (token);
}

char	*build_command_path(const char *dir, const char *cmd)
{
	int		dir_len;
	int		cmd_len;
	char	*full_path;

	cmd_len = ft_strlen(cmd);
	dir_len = ft_strlen(dir);
	full_path = malloc(dir_len + cmd_len + 2);
	if (!full_path)
		return (NULL);
	ft_strcpy(full_path, dir);
	full_path[dir_len] = '/';
	ft_strcpy(full_path + dir_len + 1, cmd);
	return (full_path);
}

char	**env_list_to_envp(t_env *env_list)
{
	int		count;
	t_env	*tmp;
	char	**envp;
	char	*entry;

	tmp = env_list;
	count = count_arg(tmp);
	envp = malloc(sizeof(char *) * (count + 1));
	if (!envp)
		return (NULL);
	tmp = env_list;
	count = 0;
	while (tmp)
	{
		entry = malloc(ft_strlen(tmp->key) + ft_strlen(tmp->value) + 2);
		if (!entry)
			return (NULL);
		ft_strcpy(entry, tmp->key);
		ft_strcat(entry, "=");
		ft_strcat(entry, tmp->value);
		envp[count++] = entry;
		tmp = tmp->next;
	}
	envp[count] = NULL;
	return (envp);
}
