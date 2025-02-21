/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorynbay <@student.42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 16:59:21 by aorynbay          #+#    #+#             */
/*   Updated: 2025/01/07 17:05:17 by aorynbay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int error_syntaxcheck(t_token **tokens)
{
    perror("exit: 258 syntax error near unexpected token `|'");
	token_clear(tokens);
    return 1;
}

static int	checker_pipe(t_token *tmp, t_token **tokens)
{
	if (ft_strcmp(tmp->next->value, "|") == 0 || ((ft_strcmp(tmp->next->value,">") == 0
		|| ft_strcmp(tmp->next->value, "<") == 0
		|| ft_strcmp(tmp->next->value, ">>") == 0 || ft_strcmp(tmp->next->value,"<<") == 0)
		&& tmp->next->next == NULL))
		return(error_syntaxcheck(tokens));
	return (0);
}

static int	check_pipes(t_token *tmp, t_token **tokens)
{
	if (tmp->next == NULL)
		return(error_syntaxcheck(tokens));
	else if (checker_pipe(tmp, tokens) == 1)
		return (1);
	return (0);
}

static int	check_append(t_token *tmp, t_token **tokens)
{
	if (tmp->next == NULL)
	{
		perror("exit: 258 syntax error near unexpected token `>'");
		token_clear(tokens);
		return (1);
	}
	else if (checker(tmp, tokens) == 1)
		return (1);
	return (0);
}

static int	check_redirection(t_token *tmp, t_token **tokens)
{
	if (tmp->next == NULL)
	{
		perror("exit: 258 syntax error near unexpected token `>'");
		token_clear(tokens);
		return (1);
	}
	else if (checker(tmp, tokens) == 1)
		return (1);
	return (0);
}

static int	check_lesser(t_token *tmp, t_token **tokens)
{
	if (tmp->next == NULL)
	{
		perror("exit: 258 exit: 258 syntax error near unexpected token `<'");
		token_clear(tokens);
		return (1);
	}
	else if (checker(tmp, tokens) == 1)
		return (1);
	return (0);
}

void	check_syntax(t_token **tokens)
{
	t_token	*tmp;
	int		flag;

	tmp = *tokens;
	flag = 0;
	while (tmp)
	{
		if (ft_strcmp(tmp->value, "clear") == 0)
		{
    		clear_screen();
    		return ;
		}
		else if (ft_strcmp(tmp->value, "<<") == 0)
			flag = check_here_doc(tmp, tokens);
		else if (ft_strcmp(tmp->value, "|") == 0)
		{
			fprintf(stderr, "entered pipe\n");
			flag = check_pipes(tmp, tokens);
		}
		else if (ft_strcmp(tmp->value, ">>") == 0)
			flag = check_append(tmp, tokens);
		else if (ft_strcmp(tmp->value, ">") == 0)
			flag = check_redirection(tmp, tokens);
		else if (ft_strcmp(tmp->value, "<") == 0)
			flag = check_lesser(tmp, tokens);
		if (flag == 1)
			return ;
		tmp = tmp->next;
	}
	return ;
}
