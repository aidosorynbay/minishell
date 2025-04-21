/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_utils_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohkhan <mohkhan@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 18:47:28 by mohkhan           #+#    #+#             */
/*   Updated: 2025/04/21 19:22:24 by mohkhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_exit(char *cmd_path, t_env_data *ev, t_cmd *cmd)
{
	ft_putstr_fd("minishell:", 2);
	ft_putstr_fd(cmd_path, 2);
	ft_putstr_fd(": Is a directory\n", 2);
	free_cmd_data(cmd, ev);
	free(cmd_path);
	exit(126);
}

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
