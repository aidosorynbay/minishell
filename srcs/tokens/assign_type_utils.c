/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_type_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorynbay <@student.42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 19:45:35 by aorynbay          #+#    #+#             */
/*   Updated: 2025/02/17 19:21:13 by aorynbay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unknown_assign(t_token **tokens)
{
	t_token	*tmp;

	tmp = *tokens;
	while (tmp)
	{
		tmp->type = TOKEN_UNKNOWN;
		tmp = tmp->next;
	}
}

void	assign_op_eof(t_token *tmp, int *expect_eof)
{
	if (*expect_eof == 1)
	{
		tmp->type = TOKEN_EOF;
		*expect_eof = 0;
	}
	else
		assign_op_type(tmp);
}

void	handle_op(t_token *tmp, int *expect_file,
					int *expect_eof, int *expect_command)
{
	if (tmp->type == 4 || tmp->type == 5 || tmp->type == 6)
		*expect_file = 1;
	else if (tmp->type == TOKEN_HEREDOC)
		*expect_eof = 1;
	else if (tmp->type == TOKEN_PIPE)
		*expect_command = 1;
}

void	handle_comman_file(t_token *tmp, t_token **tokens,
							int *expect_file, int *expect_command)
{
	if (tmp->type == 4 || tmp->type == 5 || tmp->type == 6)
		*expect_file = 1;
	else if (tmp->type == TOKEN_PIPE)
		*expect_command = 1;
	else if (*expect_file)
	{
		tmp->type = TOKEN_FILE;
		*expect_file = 0;
	}
	else if (*expect_command)
	{
		tmp->type = TOKEN_CMD;
		*expect_command = 0;
	}
	else if (tmp == *tokens)
	{
		assign_builtin_type(tmp);
		if (tmp->type == TOKEN_UNKNOWN)
			tmp->type = TOKEN_CMD;
	}
}
