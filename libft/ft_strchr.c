/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorynbay <@student.42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 14:58:26 by aorynbay          #+#    #+#             */
/*   Updated: 2024/07/06 00:28:54 by aorynbay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*str;
	int		i;

	str = (char *)s;
	i = 0;
	while (s[i] != '\0' && s[i] != (char)c)
		i++;
	if (s[i] == (char)c)
		return (str + i);
	return (NULL);
}

// #include <stdio.h>
// int	main(void)
// {
// 	char str[] = "https://www.tutorialspoint.com";
// 	char ch = '\0';
// 	char *res = ft_strchr(str, ch);

// 	printf("|%s|\n", res);
// }