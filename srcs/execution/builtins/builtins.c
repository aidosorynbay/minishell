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

static void	restore_and_cleanup(int fd[6], char **envp, t_cmd *cmd_list)
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

static void	update_exit_status(int status, t_env_data *ev)
{
	if (WIFEXITED(status))
		ev->last_exit = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		ev->last_exit = 128 + WTERMSIG(status);
	else if (g_exit_code == 1)
		ev->last_exit = g_exit_code;
}

static void	cleanup_fds(int fd[6], t_cmd *cmd)
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

static void	handle_output_redir(t_cmd *cmd, t_env_data *ev, int fd[6])
{
	if (cmd->outfile && handle_redirection(cmd->outfile, cmd->append_fd) == 1)
	{
		perror("minishell: output redirection failed");
		free_cmd_data(cmd, ev);
		exit(1);
	}
	else if (cmd->next)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		close(fd[0]);
	}
}

static void	execute_child_process(t_cmd *cmd, t_env_data *ev, int fd[6],
		char **envp)
{
	if (cmd->has_heredoc && cmd->heredoc_path)
		handle_heredoc(cmd->heredoc_path);
	else if (cmd->inputfile)
	{
		if (handle_input_redirection(cmd->inputfile) == 1)
		{
			perror("minishell: input redirection failed");
			free_cmd_data(cmd, ev);
			exit(1);
		}
	}
	else if (fd[4] != -1)
	{
		dup2(fd[4], STDIN_FILENO);
		close(fd[4]);
	}
	handle_output_redir(cmd, ev, fd);
	cleanup_fds(fd, cmd);
	execute_command(cmd, envp, ev);
	exit(EXIT_FAILURE);
}

static int	handle_input_file(t_cmd *cmd, t_env_data *ev, int nums[2])
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

static int	handle_output_file(t_cmd *cmd, t_env_data *ev, int nums[2],
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

static int	process_redirection_tokens(t_cmd *cmd, t_env_data *ev, int fd[6],
		int nums[2])
{
	if (ft_strcmp(cmd->args[nums[0]], "<") == 0)
	{
		if (handle_input_file(cmd, ev, nums) == 1)
			return (1);
		(nums[0])++;
	}
	else if (ft_strcmp(cmd->args[nums[0]], ">") == 0
		|| ft_strcmp(cmd->args[nums[0]], ">>") == 0)
	{
		if (handle_output_file(cmd, ev, nums, fd) == 1)
			return (1);
		(nums[0])++;
	}
	else if (ft_strcmp(cmd->args[nums[0]], "<<") == 0)
		(nums[0])++;
	else
	{
		cmd->args_for_cmd[nums[1]] = ft_strdup(cmd->args[nums[0]]);
		(nums[1])++;
	}
	return (0);
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

static void	implement_redir(t_cmd *cmd)
{
	if (cmd->inputfile && handle_input_redirection(cmd->inputfile) == 1)
	{
		perror("minishell: hello");
		exit(1);
	}
	if (cmd->outfile && handle_redirection(cmd->outfile, cmd->append_fd) == 1)
	{
		perror("minishell: ");
		exit(1);
	}
}

static void	free_fds(int fd[4], int *prev_fd)
{
	if (*prev_fd != -1)
		close(*prev_fd);
	close(fd[0]);
	close(fd[1]);
	close(fd[2]);
	close(fd[3]);
}

static void	setup_redirections(int fd[6], t_cmd *cmd)
{
	if (fd[4] != -1)
	{
		dup2(fd[4], STDIN_FILENO);
		close(fd[4]);
	}
	if (cmd->next && !cmd->outfile)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		close(fd[0]);
	}
}

static void	execute_builtin_child(t_cmd *cmd, t_env_data *ev, int fd[4],
		int *prev_fd)
{
	implement_redir(cmd);
	setup_redirections(fd, cmd);
	execute_builtins(cmd, ev, fd);
	free_fds(fd, prev_fd);
}

static void	single_builtin(t_cmd *cmd, t_env_data *ev, int fd[4])
{
	implement_redir(cmd);
	execute_builtins(cmd, ev, fd);
}

static int	handle_builtin(t_cmd *cmd, t_env_data *ev, int *fd, t_cmd *head)
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
			free_cmd_data(head, ev);
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
		handle_builtin(cmd, ev, fd, cmd);
	else
	{
		pid = fork();
		if (pid == 0)
		{
			execute_child_process(cmd, ev, fd, envp);
		}
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

void	init_execution(t_cmd *cmd_list, t_env_data *ev)
{
	int		status;
	t_cmd	*cmd;
	char	**envp;
	int		fd[6];
	t_cmd	*head;

	if (process_all_heredocs(cmd_list))
		return (ev->last_exit = 1, (void)0);
	init_fd(fd);
	cmd = cmd_list;
	head = cmd_list;
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
