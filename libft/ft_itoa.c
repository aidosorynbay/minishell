/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorynbay <@student.42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 12:24:12 by aorynbay          #+#    #+#             */
/*   Updated: 2024/07/02 16:29:32 by aorynbay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*memall(char *result, int n, int *count)
{
	int	tmp;

	tmp = n;
	if (n < 0)
	{
		(*count)++;
		tmp = -n;
	}
	while (tmp > 0)
	{
		(*count)++;
		tmp = tmp / 10;
	}
	result = malloc(sizeof(char) * (*count + 1));
	return (result);
}

static char	*int_to_str(char *result, int n, int count)
{
	result[count] = '\0';
	count--;
	if (n < 0)
	{
		result[0] = '-';
		n = -n;
	}
	while (n > 0 && count >= 0)
	{
		result[count] = n % 10 + '0';
		count--;
		n = n / 10;
	}
	return (result);
}

static char	*max_neg(char *result)
{
	result = malloc(sizeof(char) * 12);
	if (result == NULL)
		return (NULL);
	result[0] = '-';
	result[1] = '2';
	result[2] = '1';
	result[3] = '4';
	result[4] = '7';
	result[5] = '4';
	result[6] = '8';
	result[7] = '3';
	result[8] = '6';
	result[9] = '4';
	result[10] = '8';
	result[11] = '\0';
	return (result);
}

char	*ft_itoa(int n)
{
	char	*result;
	int		count;

	result = NULL;
	count = 0;
	if (n == 0)
	{
		result = malloc(sizeof(char) * 2);
		if (result == NULL)
			return (NULL);
		result[0] = '0';
		result[1] = '\0';
		return (result);
	}
	else if (n == -2147483648)
	{
		result = max_neg(result);
		return (result);
	}
	result = memall(result, n, &count);
	if (result == NULL)
		return (NULL);
	result = int_to_str(result, n, count);
	return (result);
}

// #include <stdio.h>
// int	main(void)
// {
// 	int n = -1234;
// 	printf("|%s|\n", ft_itoa(n));
// }