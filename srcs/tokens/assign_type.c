/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_type.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorynbay <@student.42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 12:48:59 by aorynbay          #+#    #+#             */
/*   Updated: 2025/01/29 19:37:42 by aorynbay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	assign_op_type(t_token *tmp)
{
	if (strcmp(tmp->value, "|") == 0)
		tmp->type = TOKEN_PIPE;
	else if (strcmp(tmp->value, "<") == 0)
		tmp->type = TOKEN_REDIRECT_IN;
	else if (strcmp(tmp->value, ">") == 0)
		tmp->type = TOKEN_REDIRECT_OUT;
	else if (strcmp(tmp->value, ">>") == 0)
		tmp->type = TOKEN_REDIRECT_APPEND;
	else if (strcmp(tmp->value, "<<") == 0)
		tmp->type = TOKEN_HEREDOC;
}

void	assign_builtin_type(t_token *tmp)
{
	if ((strcmp(tmp->value, "echo") == 0) || !(strcmp(tmp->value, "cd"))
		|| !(strcmp(tmp->value, "pwd")) || !(strcmp(tmp->value, "export"))
		|| !(strcmp(tmp->value, "unset")) || !(strcmp(tmp->value, "env"))
		|| !(strcmp(tmp->value, "exit")))
		tmp->type = TOKEN_BUILTIN;
}

void	assign_token_type(t_token **tokens)
{
	t_token *tmp;

	tmp = *tokens;
	while (tmp)
	{
		assign_builtin_type(tmp);
		assign_op_type(tmp);
		tmp = tmp->next;
		tmp->type = TOKEN_UNKNOWN;
	}
}
