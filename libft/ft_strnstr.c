/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorynbay <@student.42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 16:47:21 by aorynbay          #+#    #+#             */
/*   Updated: 2024/07/01 19:19:24 by aorynbay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	unsigned int	i;
	unsigned int	j;
	char			*result;

	i = 0;
	result = (char *)haystack;
	if (needle[0] == '\0')
		return (result);
	while (i < len && haystack[i] != '\0')
	{
		j = 0;
		if (needle[j] == haystack[i])
		{
			while (haystack[i + j] == needle[j] && i + j < len)
			{
				j++;
				if (needle[j] == '\0')
					return (result + i);
			}
		}
		i++;
	}
	return (0);
}

// #include <stdio.h>
// #include <string.h>
// int	main(void)
// {
// 	char str1[] = "yoobitbityoohello";
// 	char str2[] = "bitbit";
// 	printf("%s\n", strnstr(str1, str2, -2));
// 	printf("%s\n", ft_strnstr(str1, str2, -2));
// }