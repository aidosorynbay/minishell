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

static int	count_args_for_cmd(char **tokens)
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

static int	handle_builtin(t_cmd *cmd, t_env_data *ev, int fd[4], int *prev_fd, t_cmd *head)
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
			if (cmd->inputfile && handle_input_redirection(cmd->inputfile) == 1)
			{
				perror("minishell: hello");
				exit(1);
			}
			if (cmd->outfile && handle_redirection(cmd->outfile,
					cmd->append_fd) == 1)
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
			if (*prev_fd != -1)
				close(*prev_fd);
			close(fd[0]);
			close(fd[1]);
			close(fd[2]);
			close(fd[3]);
			last_exit = ev->last_exit;
			free_cmd_data(head, ev);
			exit(last_exit);
		}
		while (waitpid(-1, &status, 0) > 0)
		{
			if (WIFEXITED(status))
				ev->last_exit = WEXITSTATUS(status);
			else if (g_exit_code == 1)
				ev->last_exit = g_exit_code;
		}
		return (1);
	}
	else
	{
		if (cmd->inputfile && handle_input_redirection(cmd->inputfile) == 1)
		{
			perror("minishell: ");
			return (ev->last_exit = 1);
		}
		if (cmd->outfile && handle_redirection(cmd->outfile,
				cmd->append_fd) == 1)
		{
			perror("minishell: ");
			return (ev->last_exit = 1);
		}
		execute_builtins(cmd, ev, fd);
	}
	return (0);
}

void	init_execution(t_cmd *cmd_list, t_env_data *ev)
{
	int		prev_fd;
	int		pid;
	int		status;
	t_cmd	*cmd;
	char	**envp;
	int		i;
	int		j;
	int		arg_count;
	int		tmp_fd;
	int		is_append;
	int		fd[4];
	t_cmd	*head;

	if (process_all_heredocs(cmd_list))
	{
		ev->last_exit = 1;
		return ;
	}
	fd[2] = dup(STDOUT_FILENO);
	fd[3] = dup(STDIN_FILENO);
	if (fd[2] == -1 || fd[3] == -1)
	{
		perror("minishell: dup error");
		exit(EXIT_FAILURE);
	}
	prev_fd = -1;
	cmd = cmd_list;
	head = cmd_list;
	envp = env_list_to_envp(ev->env_list);
	if (cmd)
		cmd->envp = envp;
	while (cmd)
	{
		if (ft_strcmp(cmd->args[0], "<<") == 0)
		{
			cmd = cmd->next;
			continue ;
		}
		if (cmd && cmd->next && pipe(fd) == -1)
		{
			perror("pipe error");
			ev->last_exit = 1;
			exit(ev->last_exit);
		}
		i = 0;
		j = 0;
		arg_count = count_args_for_cmd(cmd->args);
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
					ft_putstr_fd("minishell: ", STDERR_FILENO);
					ft_putstr_fd(cmd->args[i + 1], STDERR_FILENO);
					ft_putstr_fd(": No such file or directory\n",
						STDERR_FILENO);
					ev->last_exit = 1;
					return ;
				}
				cmd->inputfile = ft_strdup(cmd->args[i + 1]);
				if (!cmd->inputfile)
					exit(EXIT_FAILURE);
				i++;
			}
			else if (ft_strcmp(cmd->args[i], ">") == 0
				|| ft_strcmp(cmd->args[i], ">>") == 0)
			{
				is_append = ft_strcmp(cmd->args[i], ">>") == 0;
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
			handle_builtin(cmd, ev, fd, &prev_fd, head);
		else
		{
			pid = fork();
			if (pid == 0)
			{
				if (cmd->has_heredoc && cmd->heredoc_path)
					handle_heredoc(cmd->heredoc_path);
				else if (cmd->inputfile)
				{
					if (handle_input_redirection(cmd->inputfile) == 1)
					{
						perror("minishell: hello bye ");
						free_cmd_data(cmd, ev);
						exit(1);
					}
				}
				else if (prev_fd != -1)
				{
					dup2(prev_fd, STDIN_FILENO);
					close(prev_fd);
				}
				if (cmd->outfile && handle_redirection(cmd->outfile,
						cmd->append_fd) == 1)
				{
					perror("minishell: hello bye ");
					free_cmd_data(cmd, ev);
					free(cmd->inputfile);
					cmd->inputfile = NULL;
					free(cmd->outfile);
					cmd->outfile = NULL;
					exit(1);
				}
				else if (cmd->next)
				{
					dup2(fd[1], STDOUT_FILENO);
					close(fd[1]);
					close(fd[0]);
				}
				close(fd[2]);
				close(fd[3]);
				if (prev_fd != -1)
				{
					close(prev_fd);
				}
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
				execute_command(cmd, envp, ev);
				exit(EXIT_FAILURE);
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
		j = 0;
		while (envp[j])
		{
			free(envp[j]);
			j++;
		}
		free(envp);
	}
	free_cmd_list(cmd_list);
	return ;
}

// void free_envp(char **envp)
// {
//     if (!envp)
//         return;

//     for (int i = 0; envp[i]; i++)
//         free(envp[i]);
//     free(envp);
// }

// void restore_standard_fds(int fd[4])
// {
//     if (dup2(fd[2], STDOUT_FILENO) == -1 || dup2(fd[3], STDIN_FILENO) == -1)
//     {
//         perror("minishell: dup2 error");
//         exit(EXIT_FAILURE);
//     }
//     close(fd[2]);
//     close(fd[3]);
// }

// void wait_for_children(t_env_data *ev)
// {
//     int status;

//     while (wait(&status) > 0)
//     {
//         if (WIFEXITED(status))
//             ev->last_exit = WEXITSTATUS(status);
//         else if (WIFSIGNALED(status))
//             ev->last_exit = 128 + WTERMSIG(status);
//     }
// }

// void exit_with_error(t_cmd *cmd, t_env_data *ev, const char *message)
// {
//     perror(message);
//     free_cmd_data(cmd, ev);
//     exit(EXIT_FAILURE);
// }

// void fork_and_execute(t_cmd *cmd, t_env_data *ev, int fd[4], int *prev_fd)
// {
//     pid_t pid = fork();

//     if (pid == 0)
//     {
//         if (cmd->has_heredoc && cmd->heredoc_path)
//             handle_heredoc(cmd->heredoc_path);
//         else if (cmd->inputfile && handle_input_redirection(cmd->inputfile) == 1)
//             exit_with_error(cmd, ev, "minishell: input redirection failed");

//         if (*prev_fd != -1)
//         {
//             dup2(*prev_fd, STDIN_FILENO);
//             close(*prev_fd);
//         }

//         if (cmd->outfile && handle_redirection(cmd->outfile, cmd->append_fd) == 1)
//             exit_with_error(cmd, ev, "minishell: output redirection failed");

//         if (cmd->next)
//         {
//             dup2(fd[1], STDOUT_FILENO);
//             close(fd[1]);
//             close(fd[0]);
//         }

//         close(fd[2]);
//         close(fd[3]);
//         execute_command(cmd, cmd->envp, ev);
//         exit(EXIT_FAILURE);
//     }
//     else if (pid == -1)
//     {
//         perror("fork error");
//         exit(EXIT_FAILURE);
//     }
// }

// int handle_redirection_tokens(t_cmd *cmd, char **args, int *i)
// {
//     if (ft_strcmp(args[*i], "<") == 0)
//     {
//         cmd->inputfile = ft_strdup(args[*i + 1]);
//         if (!cmd->inputfile)
//             exit(EXIT_FAILURE);
//         (*i) += 2;
//         return 1;
//     }
//     else if (ft_strcmp(args[*i], ">") == 0 || ft_strcmp(args[*i], ">>") == 0)
//     {
//         int is_append = ft_strcmp(args[*i], ">>") == 0;
//         cmd->outfile = ft_strdup(args[*i + 1]);
//         cmd->append_fd = is_append;
//         (*i) += 2;
//         return 1;
//     }
//     else if (ft_strcmp(args[*i], "<<") == 0)
//     {
//         (*i)++;
//         return 1;
//     }
//     return 0;
// }

// void setup_command_args(t_cmd *cmd)
// {
//     int i = 0, j = 0, arg_count = count_args_for_cmd(cmd->args);

//     if (arg_count > 0)
//     {
//         cmd->args_for_cmd = malloc(sizeof(char *) * (arg_count + 1));
//         if (!cmd->args_for_cmd)
//         {
//             perror("malloc failed");
//             exit(EXIT_FAILURE);
//         }
//     }
//     else
//         cmd->args_for_cmd = NULL;

//     while (cmd->args[i])
//     {
//         if (handle_redirection_tokens(cmd, cmd->args, &i))
//             continue;

//         cmd->args_for_cmd[j++] = ft_strdup(cmd->args[i++]);
//     }

//     if (cmd->args_for_cmd)
//         cmd->args_for_cmd[j] = NULL;
// }

// void process_command(t_cmd *cmd, t_env_data *ev, int fd[4], int *prev_fd)
// {
//     if (ft_strcmp(cmd->args[0], "<<") == 0)
//         return;

//     if (cmd->next && pipe(fd) == -1)
//     {
//         perror("pipe error");
//         ev->last_exit = 1;
//         exit(ev->last_exit);
//     }

//     setup_command_args(cmd);

//     if (cmd->cmd_type == TOKEN_BUILTIN)
//         handle_builtin(cmd, ev, fd, prev_fd);
//     else
//         fork_and_execute(cmd, ev, fd, prev_fd);

//     if (*prev_fd != -1)
//         close(*prev_fd);

//     if (cmd->next)
//     {
//         close(fd[1]);
//         *prev_fd = fd[0];
//     }
// }

// int setup_standard_fds(int fd[4])
// {
//     fd[2] = dup(STDOUT_FILENO);
//     fd[3] = dup(STDIN_FILENO);
//     if (fd[2] == -1 || fd[3] == -1)
//     {
//         perror("minishell: dup error");
//         return -1;
//     }
//     return 0;
// }

// void init_execution(t_cmd *cmd_list, t_env_data *ev)
// {
//     int fd[4];
//     int prev_fd = -1;
//     char **envp;
//     t_cmd *cmd = cmd_list;

//     if (process_all_heredocs(cmd_list))
//     {
//         ev->last_exit = 1;
//         return;
//     }

//     if (setup_standard_fds(fd) == -1)
//         return;

//     envp = env_list_to_envp(ev->env_list);
//     if (cmd)
//         cmd->envp = envp;

//     while (cmd)
//     {
//         process_command(cmd, ev, fd, &prev_fd);
//         cmd = cmd->next;
//     }

//     wait_for_children(ev);
//     restore_standard_fds(fd);
//     free_envp(envp);
//     free_cmd_list(cmd_list);
// }
