/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohkhan <mohkhan@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 18:36:10 by mohkhan           #+#    #+#             */
/*   Updated: 2025/04/21 18:36:11 by mohkhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	allocate_args_for_cmd(t_cmd *cmd)
{
	cmd->count_cmd = count_args_for_cmd(cmd->args);
	if (cmd->count_cmd > 0)
	{
		cmd->args_for_cmd = malloc(sizeof(char *) * (cmd->count_cmd + 1));
		if (!cmd->args_for_cmd)
		{
			perror("malloc failed");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		cmd->args_for_cmd = NULL;
	}
}
