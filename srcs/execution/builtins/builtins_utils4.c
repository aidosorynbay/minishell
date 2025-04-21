/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils4.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohkhan <mohkhan@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 19:37:21 by mohkhan           #+#    #+#             */
/*   Updated: 2025/04/21 19:37:22 by mohkhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	single_builtin(t_cmd *cmd, t_env_data *ev, int fd[4])
{
	implement_redir(cmd);
	execute_builtins(cmd, ev, fd);
}
