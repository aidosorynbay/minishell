/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorynbay <@student.42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 19:25:00 by aorynbay          #+#    #+#             */
/*   Updated: 2024/11/27 00:37:38 by aorynbay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/**
 * echo "''''''''''$PWD"'$PWD'"       |"cat|ls // 4 tokens > < >> << (same logic as pipe)
 * a boolean for quotation status 
 * it becomes true when it meets a quote and false when it meets the same quote type
 * anything touching the quote after it becomes unquoted is part of the token unless it is an operand
 * 
*/

void	tokenization(t_token *tokens, char *copy)
{
	int	i;

	i = -1;
	while (copy[++i])
	{
		
	}
	
}

t_token	*tokenize_input(char *input)
{
	t_token	*tokens;
	char	*copy;

	copy = ft_strdup(input);
	tokenization(tokens, copy);
}
