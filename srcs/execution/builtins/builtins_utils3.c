#include "minishell.h"

void	handle_output_redir(t_cmd *cmd, t_env_data *ev, int fd[6])
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

void	execute_child_process(t_cmd *cmd, t_env_data *ev, int fd[6],
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

int	process_redirection_tokens(t_cmd *cmd, t_env_data *ev, int fd[6],
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

void	implement_redir(t_cmd *cmd)
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

void	setup_redirections(int fd[6], t_cmd *cmd)
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
