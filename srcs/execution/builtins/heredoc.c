/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohkhan <mohkhan@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 18:47:22 by mohkhan           #+#    #+#             */
/*   Updated: 2025/04/21 18:47:23 by mohkhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_heredoc(char **heredoc_path)
{
	int	fd;

	if (*heredoc_path)
	{
		fd = open(*heredoc_path, O_RDONLY);
		if (fd == -1)
		{
			perror("open crashed");
			return ;
		}
		if (dup2(fd, STDIN_FILENO) == -1)
		{
			perror("dup2 heredoc");
			exit(EXIT_FAILURE);
		}
		close(fd);
		free(*heredoc_path);
		*heredoc_path = NULL;
	}
	return ;
}

static int	read_heredoc_path(int pipe_fd[2], char **heredoc_path)
{
	char	buffer[256];
	ssize_t	n;

	waitpid(-1, NULL, 0);
	close(pipe_fd[1]);
	n = read(pipe_fd[0], buffer, sizeof(buffer));
	if (n <= 0)
	{
		close(pipe_fd[0]);
		return (1);
	}
	buffer[n] = '\0';
	*heredoc_path = ft_strdup(buffer);
	close(pipe_fd[0]);
	return (0);
}

static void	write_heredoc_to_file(int pipe_fd[2], char *limiter)
{
	char	*filename;
	int		fd;
	char	*line;

	filename = "/tmp/.minishell_heredoc_tmp";
	fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		exit(1);
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, limiter) == 0)
		{
			free(line);
			break ;
		}
		ft_putendl_fd(line, fd);
		free(line);
	}
	close(fd);
	write(pipe_fd[1], filename, ft_strlen(filename) + 1);
	close(pipe_fd[1]);
}

int	create_heredoc(char *limiter, char **heredoc_path, t_env_data *ev, int *fd)
{
	int		pipe_fd[2];
	pid_t	pid;

	if (pipe(pipe_fd) == -1)
		return (perror("pipe"), -1);
	pid = fork();
	if (pid == -1)
		return (perror("fork"), -1);
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		close(pipe_fd[0]);
		write_heredoc_to_file(pipe_fd, limiter);
		close(fd[2]);
		close(fd[3]);
		free_cmd_data(ev->cmd_list, ev);
		exit(0);
	}
	else
		return (read_heredoc_path(pipe_fd, heredoc_path));
}

int	process_all_heredocs(t_cmd *cmd_list, t_env_data *ev, int *fd)
{
	t_cmd	*cmd;
	int		i;
	char	*heredoc_file;

	cmd = cmd_list;
	while (cmd)
	{
		cmd->heredoc_path = NULL;
		cmd->has_heredoc = 0;
		i = 0;
		while (cmd->args && cmd->args[i])
		{
			if (!ft_strcmp(cmd->args[i], "<<") && cmd->args[i + 1])
			{
				if (create_heredoc(cmd->args[i + 1], &heredoc_file, ev, fd))
					return (1);
				cmd->heredoc_path = heredoc_file;
				cmd->has_heredoc = 1;
				i++;
			}
			i++;
		}
		cmd = cmd->next;
	}
	return (0);
}
