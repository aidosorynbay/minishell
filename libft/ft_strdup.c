/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorynbay <@student.42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 16:14:01 by aorynbay          #+#    #+#             */
/*   Updated: 2024/07/06 05:59:51 by aorynbay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*result;
	int		i;

	result = malloc(sizeof(char) * (ft_strlen(s1) + 1));
	i = 0;
	if (result == NULL)
	{
		return (NULL);
	}
	while (s1[i] != '\0')
	{
		result[i] = s1[i];
		i++;
	}
	result[i] = s1[i];
	return (result);
}

// #include <stdio.h>
// int	main(void)
// {
// 	char str1[] = "word";
// 	char *str2 = ft_strdup(str1);
// 	puts(str2);
// }