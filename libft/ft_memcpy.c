/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorynbay <@student.42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 16:52:06 by aorynbay          #+#    #+#             */
/*   Updated: 2024/07/05 23:57:36 by aorynbay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	if (dst == NULL && src == NULL)
	{
		return (NULL);
	}
	while (i < n)
	{
		((char *)dst)[i] = ((char *)src)[i];
		i++;
	}
	return (dst);
}

// #include <stdio.h>
// #include <string.h>
// int	main(void)
// {
// 	char *str1 = NULL;
//     char *str2 = NULL;

// 	memcpy(str1, str2, 2);
// 	printf("%s\n", str1);

// 	char *strr1 = NULL;
//     char *strr2 = NULL;

// 	ft_memcpy(strr1, strr2, 2);
// 	printf("%s\n", strr1);
// }