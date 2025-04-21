/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorynbay <@student.42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 10:53:29 by mohkhan           #+#    #+#             */
/*   Updated: 2025/04/18 17:07:24 by aorynbay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	execute_builtin_child(t_cmd *cmd, t_env_data *ev, int fd[4],
		int *prev_fd)
{
	implement_redir(cmd);
	setup_redirections(fd, cmd);
	execute_builtins(cmd, ev, fd);
	free_fds(fd, prev_fd);
}

static int	handle_builtin(t_cmd *cmd, t_env_data *ev, int *fd)
{
	pid_t	pid;
	int		status;
	int		last_exit;

	if (!cmd || !cmd->args || !cmd->args[0])
		return (1);
	if (cmd->next)
	{
		pid = fork();
		if (pid == -1)
			return (perror("fork error"), ev->last_exit = 1);
		if (pid == 0)
		{
			execute_builtin_child(cmd, ev, fd, &fd[4]);
			last_exit = ev->last_exit;
			free_cmd_data(ev->cmd_list, ev);
			exit(last_exit);
		}
		while (waitpid(-1, &status, 0) > 0)
			update_exit_status(status, ev);
		return (1);
	}
	else
		single_builtin(cmd, ev, fd);
	return (0);
}

static void	handle_command_execution(t_cmd *cmd, t_env_data *ev, int fd[6],
		char **envp)
{
	pid_t	pid;

	if (cmd->cmd_type == TOKEN_BUILTIN)
		handle_builtin(cmd, ev, fd);
	else
	{
		pid = fork();
		if (pid == 0)
			execute_child_process(cmd, ev, fd, envp);
		else if (pid == -1)
		{
			perror("fork error");
			exit(EXIT_FAILURE);
		}
	}
	if (fd[4] != -1)
		close(fd[4]);
	if (cmd->next)
	{
		close(fd[1]);
		fd[4] = fd[0];
	}
}

/* prev fd fd[4] tmpfd fd[5] */

static void	process_command(t_cmd *cmd, t_env_data *ev, int fd[6], char **envp)
{
	int	nums[2];

	nums[0] = 0;
	nums[1] = 0;
	if (ft_strcmp(cmd->args[0], "<<") == 0)
		return (cmd = cmd->next, (void)0);
	if (cmd->next && pipe(fd) == -1)
	{
		perror("pipe error");
		ev->last_exit = 1;
		exit(ev->last_exit);
	}
	allocate_args_for_cmd(cmd);
	while (cmd->args[nums[0]])
	{
		if (process_redirection_tokens(cmd, ev, fd, nums) == 1)
			return ;
		nums[0]++;
	}
	if (cmd->args_for_cmd)
		cmd->args_for_cmd[nums[1]] = NULL;
	handle_command_execution(cmd, ev, fd, envp);
}

void	init_execution(t_cmd *cmd_list, t_env_data *ev)
{
	int		status;
	t_cmd	*cmd;
	char	**envp;
	int		fd[6];

	init_fd(fd);
	cmd = cmd_list;
	ev->cmd_list = cmd_list;
	if (process_all_heredocs(cmd_list, ev, fd))
		return (ev->last_exit = 1, (void)0);
	envp = env_list_to_envp(ev->env_list);
	if (cmd)
		cmd->envp = envp;
	while (cmd)
	{
		process_command(cmd, ev, fd, envp);
		cmd = cmd->next;
	}
	while (wait(&status) > 0)
		update_exit_status(status, ev);
	restore_and_cleanup(fd, envp, cmd_list);
	return ;
}
