/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorynbay <@student.42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 17:06:01 by aorynbay          #+#    #+#             */
/*   Updated: 2024/06/27 17:06:01 by aorynbay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_each_char(char const *s, char const *set, int i)
{
	int	j;

	j = 0;
	while (set[j] != '\0')
	{
		if (s[i] == set[j])
		{
			return (1);
		}
		j++;
	}
	return (0);
}

static int	ft_set_chars(char const *s, char const *set)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (check_each_char(s, set, i) == 1 && s[i] != '\0')
	{
		count++;
		i++;
	}
	i = ft_strlen(s) - 1;
	while (check_each_char(s, set, i) == 1 && i >= 0)
	{
		count++;
		i--;
	}
	return (count);
}

static char	*ft_no_set_str(char *result, char const *s1, char const *set)
{
	int	start;
	int	end;
	int	k;

	start = 0;
	while (s1[start] != '\0' && check_each_char(s1, set, start) == 1)
	{
		start++;
	}
	end = ft_strlen(s1) - 1;
	while (end >= start && check_each_char(s1, set, end) == 1)
	{
		end--;
	}
	k = 0;
	while (start <= end)
	{
		result[k++] = s1[start++];
	}
	result[k] = '\0';
	return (result);
}

static int	ft_same_str(char const *s1, char const *set)
{
	int		i;

	i = 0;
	while (s1[i] != '\0' && check_each_char(s1, set, i) == 1)
	{
		i++;
	}
	if (s1[i] == '\0')
	{
		return (1);
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*result;
	int		chars_to_remove;

	if (!s1 || !set)
		return (NULL);
	if (ft_same_str(s1, set) == 1)
		return (ft_strdup(""));
	chars_to_remove = ft_set_chars(s1, set);
	result = malloc(sizeof(char) * (ft_strlen(s1) - chars_to_remove + 1));
	if (result == NULL)
		return (NULL);
	result = ft_no_set_str(result, s1, set);
	return (result);
}

// int main(void)
// {
//     char str1[] = "ayo remove thesea"; // yo remove thes
// 	// printf("%zu\n", ft_strlen(str1));
//     char str2[] = "aeo";
//     printf("|%s|\n", ft_strtrim(str1, str2));
// }