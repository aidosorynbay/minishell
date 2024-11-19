/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorynbay <@student.42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 10:44:54 by aorynbay          #+#    #+#             */
/*   Updated: 2024/07/03 19:00:04 by aorynbay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**check_memall(char **arr, int i)
{
	int	j;

	j = 0;
	if (arr[i] == NULL)
	{
		while (j < i)
		{
			free(arr[j]);
			j++;
		}
		free(arr);
		return (NULL);
	}
	return (arr);
}

static char	**malloc_for_each_str(char **result, const char *s, char c)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	k = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			i++;
		else
		{
			j = 0;
			while (s[i] != c && s[i] != '\0')
			{
				j++;
				i++;
			}
			result[k] = malloc(sizeof(char) * (j + 1));
			if (check_memall(result, k) == NULL)
				return (NULL);
			k++;
		}
	}
	return (result);
}

static int	ft_word_count(const char *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
		{
			while (s[i] == c)
			{
				i++;
			}
		}
		else if (s[i] != '\0' && s[i] != c)
		{
			count++;
			while (s[i] != '\0' && s[i] != c)
			{
				i++;
			}
		}
	}
	return (count);
}

static char	**allocate_chars(char **result, const char *s, char c)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			i++;
		else
		{
			k = 0;
			while (s[i] != c && s[i] != '\0')
			{
				result[j][k++] = s[i++];
			}
			result[j++][k] = '\0';
		}
	}
	return (result);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	int		word_count;

	if (!s)
		return (NULL);
	word_count = ft_word_count(s, c);
	result = malloc(sizeof(char *) * (word_count + 1));
	if (result == NULL)
		return (NULL);
	result[word_count] = NULL;
	if (malloc_for_each_str(result, s, c) == NULL)
		return (NULL);
	result = allocate_chars(result, s, c);
	return (result);
}

// #include <stdio.h>
// int	main(void)
// {
// 	char str[] = "      split       this for   me  !       ";
// 	char sep = ' ';
// 	char **arr;

// 	arr = ft_split(str, sep);
// 	int i = 0;
// 	while (arr[i] != NULL)
// 	{
// 		printf("|%s|", arr[i]);
// 		i++;
// 	}
// 	printf("|%s|", arr[i]);
// }