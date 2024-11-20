/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorynbay <@student.42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 19:25:00 by aorynbay          #+#    #+#             */
/*   Updated: 2024/11/20 17:37:52 by aorynbay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/**
 * echo"''''''''''$PWD"'$PWD'"       |"cat|ls // 4 tokens > < >> << (same logic as pipe)
 * a boolean for quotation status 
 * it becomes true when it meets a quote and false when it meets the same quote type
 * anything touching the quote after it becomes unquoted is part of the token unless it is an operand
 * 
*/
t_token	*tokenize_input(char *input)
{
	// take input and divide with delimiters and store them in token list
}