/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorynbay <@student.42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 14:45:58 by aorynbay          #+#    #+#             */
/*   Updated: 2024/07/06 00:24:06 by aorynbay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = ft_strlen(dst);
	if (dstsize == 0)
		return (ft_strlen(src));
	if (dstsize <= ft_strlen(dst))
		return (dstsize + ft_strlen(src));
	while (src[i] != '\0' && j + i < dstsize - 1)
	{
		dst[j + i] = src[i];
		i++;
	}
	dst[j + i] = '\0';
	return (j + ft_strlen(src));
}

// #include <stdio.h>
// #include <string.h>
// int	main(void)
// {
// 	char str1[] = "Hellonyguyyoo";
// 	char str2[] = "World";

// 	size_t res = strlcat(str1, str2, 10);
// 	printf("%zu\n", res);
// 	size_t result = ft_strlcat(str1, str2, 10);
// 	printf("%zu\n", result);
// }