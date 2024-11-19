/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorynbay <@student.42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 14:10:01 by aorynbay          #+#    #+#             */
/*   Updated: 2024/07/06 00:19:32 by aorynbay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	src_len;
	size_t	i;

	src_len = ft_strlen(src);
	i = 0;
	if (dstsize == 0)
	{
		return (src_len);
	}
	while (src[i] != '\0' && i < dstsize - 1)
	{
		dst[i] = src[i];
		i++;
	}
	if (i < dstsize)
	{
		dst[i] = '\0';
	}
	return (src_len);
}

// #include <stdio.h>
// #include <string.h>
// int	main(void)
// {
// 	char str1[10] = "aida";
// 	char str2[] = "yooo";

// 	size_t result = ft_strlcpy(str1, str2, 6);
// 	printf("%zu\n", result);
// 	printf("%s\n", str1);

// 	// size_t res = strlcpy(str1, str2, 10);
// 	// printf("%zu\n", res);
// 	// printf("%s\n", str1);
// }