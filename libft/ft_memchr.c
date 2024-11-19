/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorynbay <@student.42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 16:16:44 by aorynbay          #+#    #+#             */
/*   Updated: 2024/07/06 00:36:17 by aorynbay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*str;
	size_t			i;

	str = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (str[i] == (unsigned char)c)
		{
			return (str + i);
		}
		i++;
	}
	return (NULL);
}

// #include <stdio.h>
// #include <string.h>
// int	main(void)
// {
// 	char str1[] = "https://www.tutorialspoint.com";
// 	char ch1 = '.';
// 	char *res = ft_memchr(str1, ch1, 30);
// 	printf("%s\n", res);

// 	char str2[] = "https://www.tutorialspoint.com";
// 	char ch2 = '.';
// 	char *res1 = (char *)memchr(str2, ch2, 30);
// 	printf("%s\n", res1);
// }