/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorynbay <@student.42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 15:14:46 by aorynbay          #+#    #+#             */
/*   Updated: 2024/06/28 15:27:20 by aorynbay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*str;
	int		len;

	str = (char *)s;
	len = (int)ft_strlen(s);
	if (c == '\0')
	{
		return (str + len);
	}
	while (len > 0 && s[len] != (char)c)
	{
		len--;
	}
	if (len == 0 && str[len] != (char)c)
	{
		return (NULL);
	}
	else
	{
		return (str + len);
	}
}

// #include <stdio.h>
// int	main(void)
// {
// 	char str[] = "https://www.tutorialspoint.com";
// 	char ch = '\0';
// 	char *res = ft_strrchr(str, ch);

// 	printf("|%s|\n", res);
// }