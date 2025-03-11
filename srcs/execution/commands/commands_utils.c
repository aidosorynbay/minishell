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
