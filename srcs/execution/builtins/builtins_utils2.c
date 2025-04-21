/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohkhan <mohkhan@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 19:37:15 by mohkhan           #+#    #+#             */
/*   Updated: 2025/04/21 19:37:16 by mohkhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	restore_and_cleanup(int fd[6], char **envp, t_cmd *cmd_list)
{
	if (dup2(fd[2], STDOUT_FILENO) == -1 || dup2(fd[3], STDIN_FILENO) == -1)
	{
		perror("minishell: dup2 error");
		exit(EXIT_FAILURE);
	}
	close(fd[2]);
	close(fd[3]);
	free_args(envp);
	free_cmd_list(cmd_list);
}

void	update_exit_status(int status, t_env_data *ev)
{
	if (WIFEXITED(status))
		ev->last_exit = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		ev->last_exit = 128 + WTERMSIG(status);
	else if (g_exit_code == 1)
		ev->last_exit = g_exit_code;
}

void	cleanup_fds(int fd[6], t_cmd *cmd)
{
	close(fd[2]);
	close(fd[3]);
	if (fd[4] != -1)
		close(fd[4]);
	if (cmd->next && !cmd->outfile)
	{
		close(fd[1]);
		close(fd[0]);
	}
	else if (cmd->next)
	{
		close(fd[0]);
		close(fd[1]);
	}
}

int	handle_input_file(t_cmd *cmd, t_env_data *ev, int nums[2])
{
	if (access(cmd->args[nums[0] + 1], F_OK) == -1 && !cmd->next)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(cmd->args[nums[0] + 1], STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		ev->last_exit = 1;
		return (1);
	}
	cmd->inputfile = ft_strdup(cmd->args[nums[0] + 1]);
	if (!cmd->inputfile)
		exit(EXIT_FAILURE);
	return (0);
}

int	handle_output_file(t_cmd *cmd, t_env_data *ev, int nums[2],
		int fd[6])
{
	int	is_append;

	is_append = ft_strcmp(cmd->args[nums[0]], ">>") == 0;
	fd[5] = open_fds(cmd->args[nums[0] + 1], is_append);
	if (fd[5] == 1)
	{
		perror("minishell: hello byeee");
		ev->last_exit = 1;
		return (1);
	}
	cmd->outfile = ft_strdup(cmd->args[nums[0] + 1]);
	cmd->append_fd = is_append;
	return (0);
}
