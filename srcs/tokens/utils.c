/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorynbay <@student.42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 17:40:20 by aorynbay          #+#    #+#             */
/*   Updated: 2025/02/17 17:41:59 by aorynbay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear_screen(void)
{
	write(STDOUT_FILENO, "\033[H\033[J", 6);
}

void	free_all(t_token *tokens, t_cmd *cmd)
{
	t_cmd	*tmp;

	token_clear(&tokens);
	while (cmd)
	{
		free(cmd->args);
		tmp = cmd;
		cmd = cmd->next;
		free(tmp);
	}
}
