/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorynbay <@student.42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 17:03:28 by aorynbay          #+#    #+#             */
/*   Updated: 2025/01/07 17:36:42 by aorynbay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	checker(t_token *tmp, t_token **tokens)
{
	if (ft_strcmp(tmp->next->value, "<<") == 0 || ft_strcmp(tmp->next->value,
			">") == 0 || ft_strcmp(tmp->next->value, "<") == 0
		|| ft_strcmp(tmp->next->value, ">>") == 0 || ft_strcmp(tmp->next->value,
			"|") == 0 || ft_strcmp(tmp->next->value, ";") == 0)
	{
		perror("exit: 258 syntax error near unexpected token `<<'");
		token_clear(tokens);
		return (1);
	}
	return (0);
}

int	check_here_doc(t_token *tmp, t_token **tokens)
{
	if (tmp->next == NULL)
	{
		perror("exit: 258 syntax error near unexpected token `<'");
		token_clear(tokens);
		return (1);
	}
	else if (checker(tmp, tokens) == 1)
		return (1);
	return (0);
}

int	error_syntaxcheck(t_token **tokens)
{
	perror("exit: 258 syntax error near unexpected token `|'");
	token_clear(tokens);
	return (1);
}

// int	checker_pipe(t_token *tmp, t_token **tokens)
// {
// 	if (tmp->next == NULL)
// 		return (error_syntaxcheck(tokens));
// 	else if ((ft_strcmp(tmp->next->value, "|") == 0
// 			|| (ft_strcmp(tmp->next->value, ">") == 0
// 				|| ft_strcmp(tmp->next->value, "<") == 0
// 				|| ft_strcmp(tmp->next->value, ">>") == 0
// 				|| ft_strcmp(tmp->next->value, "<<") == 0))
// 		&& tmp->next->next == NULL)
// 		return (error_syntaxcheck(tokens));
// 	return (0);
// }
