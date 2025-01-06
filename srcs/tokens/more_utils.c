/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorynbay <@student.42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 09:56:11 by aorynbay          #+#    #+#             */
/*   Updated: 2025/01/06 14:39:27 by aorynbay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_double_pipe(char *copy, int *i, t_token **tokens)
{
	if (copy[*i] == '|' && copy[*i + 1] == '|')
	{
		perror("Syntax error.");
		token_clear(*tokens);
		free(copy);
		exit(1);
	}
}

void	quote_error(t_quote_status quote)
{
	if (quote != Q_NONE)
	{
		perror("quotes error.");
		exit(1);
	}
}

void	assign_quote(char *copy, int *i, t_quote_status *quote)
{
	if (copy[*i] == '\'' && *quote == Q_NONE)
		*quote = Q_SINGLE;
	else if (copy[*i] == '"' && *quote == Q_NONE)
		*quote = Q_DOUBLE;
	else if ((copy[*i] == '\'' && *quote == Q_SINGLE)
		|| (copy[*i] == '"' && *quote == Q_DOUBLE))
		*quote = Q_NONE;
}

void	create_and_add_token(t_token **tokens, char *copy, int start, int end)
{
	t_token	*curr;

	curr = malloc(sizeof(t_token));
	if (!curr)
		return ;
	create_token(curr, &copy[start], end - start);
	curr->status = Q_NONE;
	token_add_back(tokens, curr);
}
