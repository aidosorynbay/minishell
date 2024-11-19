/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorynbay <@student.42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 13:07:27 by aorynbay          #+#    #+#             */
/*   Updated: 2024/07/05 23:52:38 by aorynbay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*arr;
	size_t			i;

	i = 0;
	arr = (unsigned char *)b;
	while (i < len)
	{
		arr[i++] = (unsigned char)c;
	}
	return (b);
}

// #include <stdio.h>
// #include <string.h>
// int	main(void)
// {
// 	unsigned char str[] = "GeeksForGeeks is for programming geeks.";
// 	ft_memset(str + 13, '.', 8 * sizeof(char));
// 	printf("%s\n", str);
// 	memset(str + 1, 'a', 3 * sizeof(char));
// 	printf("%s\n", str);
// }