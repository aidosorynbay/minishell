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

static int count_args_for_cmd(char **tokens)
{
	int count = 0;
	int i = 0;

	while (tokens[i])
	{
		if (!ft_strcmp(tokens[i], "<") || !ft_strcmp(tokens[i], ">") ||
			!ft_strcmp(tokens[i], ">>") || !ft_strcmp(tokens[i], "<<"))
		{
			i += 2;
		}
		else if (!ft_strcmp(tokens[i], "|"))
			break;
		else
		{
			count++;
			i++;
		}
	}
	return count;
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

static int handle_builtin(t_cmd *cmd, t_env_data *ev, int fd[4], int *prev_fd)
{
	pid_t   pid;
	int     status;

	if (!cmd || !cmd->args || !cmd->args[0])
		return 1;
	if (cmd->next)
	{
		pid = fork();
		if (pid == -1)
			return(perror("fork error"), ev->last_exit = 1);
		if (pid == 0)
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
			if (*prev_fd != -1)
			{
				dup2(*prev_fd, STDIN_FILENO);
				close(*prev_fd);
			}
			if (cmd->next && !cmd->outfile)
			{
				dup2(fd[1], STDOUT_FILENO);
				close(fd[1]);
				close(fd[0]);
			}
			execute_builtins(cmd, ev, fd);
			if (cmd->next)
			{
				dup2(fd[1], STDOUT_FILENO);
				close(fd[1]);
				close(fd[0]);
			}
			// free_args_for_cmd(environ);
			int last_exit = ev->last_exit;
			free_args_for_cmd(cmd->args_for_cmd);
			free_args_for_cmd(cmd->args);
			free_args_for_cmd(cmd->envp);
			free_env_data(ev);
			ev = NULL;
			// free_cmd_list(cmd);
			// free(cmd);
			// if (cmd)
			exit(last_exit);
		}
		while (waitpid(-1, &status, 0) > 0)
		{
			if (WIFEXITED(status))
				ev->last_exit = WEXITSTATUS(status);
			else if (g_exit_code == 1)
				ev->last_exit = g_exit_code;
		}
		return 1;
	}
	else
	{
		if (cmd->inputfile && handle_input_redirection(cmd->inputfile) == 1)
		{
				perror("minishell: ");
				return (ev->last_exit = 1);
		}
		if (cmd->outfile && handle_redirection(cmd->outfile, cmd->append_fd) == 1)
		{
				perror("minishell: ");
				return(ev->last_exit = 1);
		}
		execute_builtins(cmd, ev, fd);
	}
	return 0;
}

void	init_execution(t_cmd *cmd_list, t_env_data *ev)
{
	if(process_all_heredocs(cmd_list))
	{
		ev->last_exit = 1;
		return;
	}
	int		fd[4]; //fd[2] - saved_stdout, fd[3] - saved_stdin
	int		prev_fd;
	int		pid;
	int		status;
	t_cmd	*cmd;
	char	**envp;

	fd[2] = dup(STDOUT_FILENO);
	fd[3] = dup(STDIN_FILENO);
	if (fd[2] == -1 || fd[3] == -1)
	{
		perror("minishell: dup error");
		exit(EXIT_FAILURE);
	}
	prev_fd = -1;
	cmd = cmd_list;
	envp = env_list_to_envp(ev->env_list);
	if (cmd)
		cmd->envp = envp;
	while (cmd)
	{
		if (ft_strcmp(cmd->args[0], "<<") == 0)
		{
			cmd = cmd->next;
			continue;
		}
		if (cmd && cmd->next && pipe(fd) == -1)
		{
			perror("pipe error");
			ev->last_exit = 1;
			exit(ev->last_exit);
		}
		int i = 0;
		int j = 0;
		int arg_count = count_args_for_cmd(cmd->args);
		if (arg_count > 0)
		{
			cmd->args_for_cmd = malloc(sizeof(char *) * (arg_count + 1));
			if (!cmd->args_for_cmd)
			{
				perror("malloc failed");
				exit(EXIT_FAILURE);
			}
		}
		else
			cmd->args_for_cmd = NULL;
		cmd->inputfile = NULL;
		cmd->outfile = NULL;
		while (cmd->args[i])
		{
			if (ft_strcmp(cmd->args[i], "<") == 0)
			{
				if (access(cmd->args[i + 1], F_OK) == -1 && !cmd->next)
				{
					fprintf(stderr, "minishell: %s: No such file or directory\n", cmd->args[i + 1]);
					ev->last_exit = 1;
					return ;
				}
				cmd->inputfile = ft_strdup(cmd->args[i + 1]);
				if (!cmd->inputfile)
					exit(EXIT_FAILURE);
				i++;
			}
			else if (ft_strcmp(cmd->args[i], ">") == 0 || ft_strcmp(cmd->args[i], ">>") == 0)
			{
				int tmp_fd;
				int is_append = ft_strcmp(cmd->args[i], ">>") == 0;
				
				tmp_fd = open_fds(cmd->args[i + 1], is_append);
				if (tmp_fd == 1)
				{
					perror("minishell: hello byeee");
					ev->last_exit = 1;
					return ;
				}
				cmd->outfile = strdup(cmd->args[i + 1]);
				cmd->append_fd = is_append;
				i++;
			}
			else if (ft_strcmp(cmd->args[i], "<<") == 0)
				i++;
			else
			{
				cmd->args_for_cmd[j] = ft_strdup(cmd->args[i]);
				j++;
			}
			i++;
		}
		if (cmd->args_for_cmd)
			cmd->args_for_cmd[j] = NULL;
		if (cmd->cmd_type == TOKEN_BUILTIN)
			handle_builtin(cmd, ev, fd, &prev_fd);
		else
		{
			pid = fork();
			if (pid == 0)
			{
				if (cmd->has_heredoc && cmd->heredoc_path)
					handle_heredoc(cmd->heredoc_path);
				else if (cmd->inputfile)
				{
					if(handle_input_redirection(cmd->inputfile) == 1)
					{
						perror("minishell: hello bye ");
						exit(1);
					}
				}
				else if (prev_fd != -1)
				{
					dup2(prev_fd, STDIN_FILENO);
					close(prev_fd);
				}

				if (cmd->outfile)
				{
					if(handle_redirection(cmd->outfile, cmd->append_fd) == 1)
					{
						perror("minishell: bye");
						ev->last_exit = 1;
						exit(ev->last_exit);
					}
				}
				else if (cmd->next)
				{
					dup2(fd[1], STDOUT_FILENO);
					close(fd[1]);
					close(fd[0]);
				}
				if (!ft_strcmp(cmd->args[0], ">") || !ft_strcmp(cmd->args[0], ">>") || !ft_strcmp(cmd->args[0], "<"))
					exit(1);
				execute_command(cmd, envp, ev);
			}
			else if (pid == -1)
			{
				perror("fork error");
				exit(EXIT_FAILURE);
			}
		}
		if (prev_fd != -1)
			close(prev_fd);
		if (cmd->next)
		{
			close(fd[1]);
			prev_fd = fd[0];
		}
		cmd = cmd->next;
	}
	while (wait(&status) > 0)
	{
		if (WIFEXITED(status))
			ev->last_exit = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			ev->last_exit = 128 + WTERMSIG(status);
		else if (g_exit_code == 1)
			ev->last_exit = g_exit_code;
	}
	if (dup2(fd[2], STDOUT_FILENO) == -1 || dup2(fd[3], STDIN_FILENO) == -1)
	{
		perror("minishell: dup2 error");
		exit(EXIT_FAILURE);
	}
	close(fd[2]);
	close(fd[3]);
	if (envp)
	{
		int i = 0;
		while (envp[i])
		{
			free(envp[i]);
			i++;
		}
		free(envp);
	}
	free_cmd_list(cmd_list);
	return ;
}
