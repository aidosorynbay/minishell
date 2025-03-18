/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorynbay <@student.42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 23:48:49 by aorynbay          #+#    #+#             */
/*   Updated: 2025/03/19 00:53:03 by aorynbay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_env_value(char *key, t_env *env, int last_exit)
{
	static char	exit_str[12];

	if (!key)
		return (NULL);
	if (!strcmp(key, "?"))
	{
		sprintf(exit_str, "%d", last_exit);
		return (exit_str);
	}
	while (env)
	{
		if (!strcmp(env->key, key))
			return (env->value);
		env = env->next;
	}
	return (""); // Return empty string if variable not found
}

char	*expand_variables(char *input, t_env_data *data)
{
	char	*result;
	char	*var_value;
	char	var_name[256];
	int		i, j;

	if (!input)
		return (NULL);
	result = strdup(""); // Start with an empty result
	i = 0;
	while (input[i])
	{
		if (input[i] == '$' && input[i + 1])
		{
			i++; // Skip '$'
			if (input[i] == '?') // Special case for $?
			{
				var_value = get_env_value("?", data->env, data->last_exit);
				result = realloc(result, strlen(result) + strlen(var_value) + 1);
				strcat(result, var_value);
				i++;
			}
			else if (isalnum(input[i]) || input[i] == '_')
			{
				j = 0;
				while (input[i] && (isalnum(input[i]) || input[i] == '_')) // Extract var name
					var_name[j++] = input[i++];
				var_name[j] = '\0';
				var_value = get_env_value(var_name, data->env, data->last_exit);
				result = realloc(result, strlen(result) + strlen(var_value) + 1);
				strcat(result, var_value);
			}
		}
		else
		{
			result = realloc(result, strlen(result) + 2);
			strncat(result, &input[i], 1);
			i++;
		}
	}
	return (result);
}
