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

void	ft_strcat(char *dst, const char *src)
{
	while (*dst)
		dst++;
	while (*src)
		*dst++ = *src++;
	*dst = '\0';
}

int	find_char(char *str, char *charset)
{
	int	i;
	int	j;

	i = 0;
	while (str[i])
	{
		j = 0;
		while (charset[j])
		{
			if (str[i] == charset[j])
				return (i);
			j++;
		}
		i++;
	}
	return (i);
}

void	ft_strcpy(char *dst, const char *src)
{
	while (*src)
		*dst++ = *src++;
	*dst = '\0';
}

void	ft_strncpy(char *dst, const char *src, size_t len)
{
	int	rest;

	if (ft_strlen(src) < len)
	{
		rest = len - ft_strlen(src);
		while (*src)
		{
			*dst++ = *src++;
		}
		while (rest)
		{
			*dst++ = '\0';
			rest--;
		}
	}
	else
	{
		while (len)
		{
			*dst++ = *src++;
			len--;
		}
	}
}

char	**env_list_to_envp(t_env *env_list)
{
	int		count = 0;
	t_env	*tmp = env_list;
	char	**envp;
	char	*entry;

	// Count number of env variables
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	envp = malloc(sizeof(char *) * (count + 1));
	if (!envp)
		return (NULL);
	tmp = env_list;
	count = 0;
	while (tmp)
	{
		entry = malloc(ft_strlen(tmp->key) + ft_strlen(tmp->value) + 2);
		if (!entry)
			return (NULL); // You can free previous entries if you want
		ft_strcpy(entry, tmp->key);
		ft_strcat(entry, "=");
		ft_strcat(entry, tmp->value);
		envp[count++] = entry;
		tmp = tmp->next;
	}
	envp[count] = NULL;
	return (envp);
}
