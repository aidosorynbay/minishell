/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: aorynbay <@student.42abudhabi.ae>          +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2025/01/07 16:59:21 by aorynbay          #+#    #+#             */
/*   Updated: 2025/01/07 17:05:17 by aorynbay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	checker_pipe(t_token *tmp, t_token **tokens)
{
	if (ft_strcmp(tmp->next->value, "|") == 0 || ((ft_strcmp(tmp->next->value,
					">") == 0 || ft_strcmp(tmp->next->value, "<") == 0
				|| ft_strcmp(tmp->next->value, ">>") == 0
				|| ft_strcmp(tmp->next->value, "<<") == 0)
			&& tmp->next->next == NULL))
		return (error_syntaxcheck(tokens));
	return (0);
}

static int	check_pipes(t_token *tmp, t_token **tokens, int i)
{
	if (ft_strcmp(tmp->value, "|") == 0 && i == 0)
	{
		ft_putstr_fd("exit: 258 syntax error near unexpected token `|'\n", 2);
		token_clear(tokens);
		return (258);
	}
	if (tmp->next == NULL)
		return (error_syntaxcheck(tokens));
	else if (checker_pipe(tmp, tokens) == 258)
		return (258);
	return (0);
}

static int	check_append(t_token *tmp, t_token **tokens)
{
	if (tmp->next == NULL)
	{
		perror("exit: 258 syntax error near unexpected token `>'");
		token_clear(tokens);
		return (258);
	}
	else if (checker(tmp, tokens) == 258)
		return (258);
	return (0);
}

static int	check_redirection(t_token *tmp, t_token **tokens)
{
	if (tmp->next == NULL)
	{
		perror("exit: 258 syntax error near unexpected token `>'");
		token_clear(tokens);
		return (258);
	}
	else if (checker(tmp, tokens) == 258)
		return (258);
	return (0);
}

int	check_syntax(t_token **tokens)
{
	t_token	*tmp;
	int		flag;
	int		i;

	tmp = *tokens;
	flag = 0;
	i = 0;
	while (tmp)
	{
		if (ft_strcmp(tmp->value, "clear") == 0)
			return (clear_screen(), 0);
		else if (ft_strcmp(tmp->value, "<<") == 0)
			flag = check_here_doc(tmp, tokens);
		else if (ft_strcmp(tmp->value, "|") == 0)
			flag = check_pipes(tmp, tokens, i);
		else if (ft_strcmp(tmp->value, ">>") == 0)
			flag = check_append(tmp, tokens);
		else if (ft_strcmp(tmp->value, ">") == 0)
			flag = check_redirection(tmp, tokens);
		else if (ft_strcmp(tmp->value, "<") == 0)
			flag = check_lesser(tmp, tokens);
		if (flag != 0)
			return (flag);
		tmp = tmp->next;
		i++;
	}
	return (0);
}
