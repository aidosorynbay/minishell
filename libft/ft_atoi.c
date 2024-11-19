/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorynbay <@student.42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 15:36:24 by aorynbay          #+#    #+#             */
/*   Updated: 2024/07/06 17:32:31 by aorynbay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	unsigned long long	result;
	int					sign;

	result = 0;
	sign = 1;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		result = (result * 10) + (*str - '0');
		if (result >= LLONG_MAX && sign == -1)
			return (0);
		if (result >= LLONG_MAX)
			return (-1);
		str++;
	}
	return (result * sign);
}

// #include <stdio.h>
// int	main(void)
// {
// 	char str[] = "9223372036854775806";
// 	printf("%i\n", atoi(str));
// 	printf("%i\n", ft_atoi(str));
// }
