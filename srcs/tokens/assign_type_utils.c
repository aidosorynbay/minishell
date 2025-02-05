/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_type_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorynbay <@student.42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 19:45:35 by aorynbay          #+#    #+#             */
/*   Updated: 2025/02/05 19:51:19 by aorynbay         ###   ########.fr       */
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