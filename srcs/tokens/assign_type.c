/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_type.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorynbay <@student.42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 12:48:59 by aorynbay          #+#    #+#             */
/*   Updated: 2025/02/10 17:34:20 by aorynbay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	assign_op_type(t_token *tmp)
{
	if (ft_strcmp(tmp->value, "|") == 0)
		tmp->type = TOKEN_PIPE;
	else if (ft_strcmp(tmp->value, "<") == 0)
		tmp->type = TOKEN_REDIRECT_IN;
	else if (ft_strcmp(tmp->value, ">") == 0)
	{
		tmp->type = TOKEN_REDIRECT_OUT;
	}
	else if (ft_strcmp(tmp->value, ">>") == 0)
	{
		tmp->type = TOKEN_REDIRECT_APPEND;
	}
	else if (ft_strcmp(tmp->value, "<<") == 0)
		tmp->type = TOKEN_HEREDOC;
}

void	assign_builtin_type(t_token *tmp)
{
	if ((ft_strcmp(tmp->value, "echo") == 0) || !(ft_strcmp(tmp->value, "cd"))
		|| !(ft_strcmp(tmp->value, "pwd")) || !(ft_strcmp(tmp->value, "export"))
		|| !(ft_strcmp(tmp->value, "unset")) || !(ft_strcmp(tmp->value, "env"))
		|| !(ft_strcmp(tmp->value, "exit")))
	{
		tmp->type = TOKEN_BUILTIN;
	}
}

void	assign_builtin_flag(t_token *tmp)
{
	if (ft_strcmp(tmp->value, "-n") == 0)
		tmp->type = TOKEN_BUILTIN_FLAG;
}

void	assign_token_type(t_token **tokens)
{
	t_token *tmp;
	int		expect_file;
	int		expect_command;
	int		expect_EOF;

	tmp = *tokens;
	expect_file = 0;
	expect_command = 0;
	expect_EOF = 0;
	while (tmp)
	{
		if (expect_EOF == 1)
		{
			tmp->type = TOKEN_EOF;
			expect_EOF = 0;
		}
		else
			assign_op_type(tmp);
		if (tmp->type == 4 || tmp->type == 5 || tmp->type == 6)
			expect_file = 1;
		else if (tmp->type == TOKEN_HEREDOC)
			expect_EOF = 1;
		else if (tmp->type == TOKEN_PIPE)
			expect_command = 1;
		else if (expect_file)
		{
			tmp->type = TOKEN_FILE;
			expect_file = 0;
		}
		else if (tmp == *tokens)
		{
			assign_builtin_type(tmp);
			if (tmp->type == TOKEN_UNKNOWN)
				tmp->type = TOKEN_CMD;
		}
		else if (expect_command)
		{
			tmp->type = TOKEN_CMD;
			expect_command = 0;
		}
		else
		{
			assign_builtin_flag(tmp);
			if (tmp->type == TOKEN_UNKNOWN)
				tmp->type = TOKEN_ARG;
		}
		tmp = tmp->next;
	}
}
