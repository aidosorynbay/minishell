/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   converter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohkhan <mohkhan@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 10:56:00 by mohkhan           #+#    #+#             */
/*   Updated: 2025/02/22 10:56:02 by mohkhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
i[2]   -> i[0] = i; i[1] = count;
*/
char	**convert_tokens_to_args(t_token **tokens)
{
	t_token	*tmp;
	char	**args;
	int		i[2];

	tmp = *tokens;
	i[1] = 0;
	i[0] = 0;
	while (tmp)
	{
		i[1]++;
		tmp = tmp->next;
	}
	args = (char **)malloc((i[1] + 1) * sizeof(char *));
	if (!args)
		return (NULL);
	tmp = *tokens;
	while (i[0] < i[1])
	{
		args[i[0]] = strdup(tmp->value);
		i[0]++;
		tmp = tmp->next;
	}
	args[i[1]] = NULL;
	token_clear(tokens);
	return (args);
}
