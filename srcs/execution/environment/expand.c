/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorynbay <@student.42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 20:48:31 by aorynbay          #+#    #+#             */
/*   Updated: 2025/04/14 20:39:33 by aorynbay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Append a single char
static char	*strjoin_char_and_free(char *s, char c)
{
	char	str[2];
	char	*tmp;

	str[0] = c;
	str[1] = '\0';
	tmp = ft_strjoin(s, str);
	free(s);
	return (tmp);
}

// Append and free first string
static char	*strjoin_and_free(char *s1, char *s2)
{
	char	*tmp;

	tmp = ft_strjoin(s1, s2);
	free(s1);
	return (tmp);
}

// Returns value for a given env key from the linked list
static char	*get_value(t_env *env_list, char *key)
{
	while (env_list)
	{
		if (ft_strcmp(env_list->key, key) == 0)
			return (env_list->value);
		env_list = env_list->next;
	}
	return (NULL);
}


char	*expand_variable(char *str, t_env_data *env_data)
{
	int		i;
	char	*result;
	char	*tmp;
	char	*var_name;
	char	*var_value;

	if (str[0] == '\'' && str[ft_strlen(str) - 1] == '\'')
		return (ft_substr(str, 1, ft_strlen(str) - 2));

	result = ft_strdup("");
	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			i++;
			if (str[i] == '?')
			{
				tmp = ft_itoa(env_data->last_exit);
				result = strjoin_and_free(result, tmp);
				i++;
			}
			else if (ft_isalpha(str[i]) || str[i] == '_')
			{
				int	start = i;
				while (ft_isalnum(str[i]) || str[i] == '_')
					i++;
				var_name = ft_substr(str, start, i - start);
				var_value = get_value(env_data->env_list, var_name);
				free(var_name);
				if (var_value)
					result = strjoin_and_free(result, var_value);
			}
			else
				result = strjoin_char_and_free(result, '$');
		}
		else
		{
			result = strjoin_char_and_free(result, str[i]);
			i++;
		}
	}
	return (result);
}


void	expand_variables(t_token **tokens, t_env_data *env_data)
{
	t_token	*curr;
	char	*expanded;

	curr = *tokens;
	while (curr)
	{
		if (curr->value && (ft_strchr(curr->value, '$')))
		{
			expanded = expand_variable(curr->value, env_data);
			free(curr->value);
			curr->value = expanded;
		}
		curr = curr->next;
	}
}

