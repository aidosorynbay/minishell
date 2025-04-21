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

void	init_fd(int fd[6])
{
	fd[2] = dup(STDOUT_FILENO);
	fd[3] = dup(STDIN_FILENO);
	if (fd[2] == -1 || fd[3] == -1)
	{
		perror("minishell: dup error");
		exit(1);
	}
	fd[4] = -1;
}

void	execute_builtins(t_cmd *cmd, t_env_data *ev, int fd[4])
{
	if (ft_strcmp(cmd->args[0], "echo") == 0)
		ev->last_exit = ft_echo(cmd->args_for_cmd);
	else if (ft_strcmp(cmd->args[0], "pwd") == 0)
		ev->last_exit = ft_pwd();
	else if (ft_strcmp(cmd->args[0], "cd") == 0)
		ev->last_exit = ft_cd(cmd->args_for_cmd);
	else if (ft_strcmp(cmd->args[0], "env") == 0)
		ev->last_exit = ft_env(ev->env_list);
	else if (ft_strcmp(cmd->args[0], "export") == 0)
		ev->last_exit = ft_export(ev, cmd->args_for_cmd);
	else if (ft_strcmp(cmd->args[0], "unset") == 0)
		ev->last_exit = ft_unset(ev, cmd->args_for_cmd);
	else if (ft_strcmp(cmd->args[0], "exit") == 0)
	{
		ev->last_exit = ft_exit(ev, cmd, fd);
		if (ev->last_exit != 1)
			exit(ev->last_exit);
	}
	else
	{
		ev->last_exit = 1;
		ft_putstr_fd("minishell: command not found\n", STDERR_FILENO);
	}
}

int	count_args_for_cmd(char **tokens)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (tokens[i])
	{
		if (!ft_strcmp(tokens[i], "<") || !ft_strcmp(tokens[i], ">")
			|| !ft_strcmp(tokens[i], ">>") || !ft_strcmp(tokens[i], "<<"))
		{
			i += 2;
		}
		else if (!ft_strcmp(tokens[i], "|"))
			break ;
		else
		{
			count++;
			i++;
		}
	}
	return (count);
}

void	free_fds(int fd[4], int *prev_fd)
{
	if (*prev_fd != -1)
		close(*prev_fd);
	close(fd[0]);
	close(fd[1]);
	close(fd[2]);
	close(fd[3]);
}
