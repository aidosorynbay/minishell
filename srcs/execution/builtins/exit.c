/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohkhan <mohkhan@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 10:55:20 by mohkhan           #+#    #+#             */
/*   Updated: 2025/04/21 12:44:56 by mohkhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_numeric_args(t_cmd *cmd, t_env_data *ev, int fd[4])
{
	int	i;

	i = 0;
	while (cmd->args_for_cmd[1][i])
	{
		if (!ft_isdigit(cmd->args_for_cmd[1][i]) && !(i == 0
				&& (cmd->args_for_cmd[1][i] == '-'
					|| cmd->args_for_cmd[1][i] == '+')))
		{
			ft_putstr_fd("minishell: exit: ", 2);
			ft_putstr_fd(cmd->args_for_cmd[1], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			free_env_data(ev);
			free_cmd(cmd, fd);
			exit(255);
		}
		i++;
	}
}

int	ft_exit(t_env_data *ev, t_cmd *cmd, int fd[4])
{
	int	exit_code;

	exit_code = 0;
	ft_putstr_fd("exit\n", 2);
	if (!cmd->args_for_cmd[1])
	{
		free_env_data(ev);
		free_cmd(cmd, fd);
		exit(exit_code);
	}
	check_numeric_args(cmd, ev, fd);
	exit_code = ft_atoi(cmd->args_for_cmd[1]);
	if (cmd->args_for_cmd[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return (1);
	}
	free_env_data(ev);
	free_cmd(cmd, fd);
	exit(exit_code);
}
