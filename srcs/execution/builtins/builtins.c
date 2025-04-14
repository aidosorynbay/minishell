/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorynbay <@student.42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 10:53:29 by mohkhan           #+#    #+#             */
/*   Updated: 2025/04/12 06:11:48 by aorynbay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int count_args_for_cmd(char **tokens)
{
	int count = 0;
	int start = 0;
	while (tokens[start] && ft_strcmp(tokens[start], "|") != 0 && 
	   ft_strcmp(tokens[start], ">") != 0 && 
	   ft_strcmp(tokens[start], ">>") != 0 && 
	   ft_strcmp(tokens[start], "<") != 0)
	{
		count++;
		start++;
	}
	return count;
}

int handle_redirection(char *outfile, int append)
{
	int fd;

	if (outfile)
	{
		if (append)
			fd = open(outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
			fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
			return(perror("minishell: redirection error"), 1);
		if(dup2(fd, STDOUT_FILENO) == -1)
			perror("DUP2 DUPPPED"); // Redirect stdout to file 
		close(fd);
	}
	return(0);
}

void handle_input_redirection(char *infile)
{
	int fd;
	if (infile)
	{
		fd = open(infile, O_RDONLY);
		if (fd == -1)
			return(perror("minishell: input redirection error"), (void)0);
		if (dup2(fd, STDIN_FILENO) == -1)
			return(perror("Dup2 got dupped\n"), (void)0);
		close(fd);
	}
}

static void handle_builtin(t_cmd *cmd, t_env_data *ev, int fd[2], int *prev_fd)
{
	pid_t   pid;
	int     status;

	if (!cmd || !cmd->args || !cmd->args[0])
		return;
	
	// Always fork if part of a pipeline
	if (cmd->next)
	{
		pid = fork();
		if (pid == -1)
		{
			perror("fork error");
			exit(EXIT_FAILURE);
		}
		if (pid == 0) // Child process
		{
			if (cmd->inputfile)
				handle_input_redirection(cmd->inputfile);
			if (cmd->outfile)
				handle_redirection(cmd->outfile, cmd->append_fd);
			
			if (*prev_fd != -1)
			{
				dup2(*prev_fd, STDIN_FILENO);
				close(*prev_fd); // FIX: Close previous pipe read end in child
			}

			// Redirect current command's output to pipe
			if (cmd->next)
			{
				dup2(fd[1], STDOUT_FILENO);
				close(fd[1]); // FIX: Close write end of pipe in child
				close(fd[0]); // FIX: Close read end of pipe in child
			}
			// Close unused pipe ends to prevent blocking
			if (cmd->next)
			{
				close(fd[0]); // Close read end
				close(fd[1]); // Close write end
			}
			// Execute the built-in
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
				ev->last_exit = ft_exit(cmd->args_for_cmd);
				exit(ev->last_exit); // Exit the shell
			}
			exit(EXIT_SUCCESS);
		}
		while (waitpid(-1, &status, 0) > 0)
		{
			if (WIFEXITED(status))
				ev->last_exit = WEXITSTATUS(status); // Update exit code for the last command
		}
		return;
	}
	else
	{
		if (cmd->inputfile)
			handle_input_redirection(cmd->inputfile);
		if (cmd->outfile)
			handle_redirection(cmd->outfile, cmd->append_fd);
			// Execute normally if not in a pipeline
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
			ev->last_exit = ft_exit(cmd->args_for_cmd);
			exit(ev->last_exit); // Exit the shell
		}
	}
}


void process_all_heredocs(t_cmd *cmd_list)
{
	t_cmd	*cmd;
	int		i;

	cmd = cmd_list;
	while (cmd)
	{
		cmd->heredoc_path = NULL;
		cmd->has_heredoc = 0;
		i = 0;
		while (cmd->args && cmd->args[i])
		{
			if (ft_strcmp(cmd->args[i], "<<") == 0)
			{
				if (!cmd->args[i + 1])
				{
					fprintf(stderr, "minishell: syntax error near unexpected token `newline'\n");
					exit(EXIT_FAILURE);
				}
				// Clean up old heredoc path if it exists
				if (cmd->heredoc_path)
				{
					free(cmd->heredoc_path);
					cmd->heredoc_path = NULL;
				}
				cmd->heredoc_path = ft_heredoc(cmd->args[i + 1]);
				if (!cmd->heredoc_path)
				{
					perror("minishell: heredoc failed");
					exit(EXIT_FAILURE);
				}
				cmd->has_heredoc = 1;
				i++; // skip delimiter
			}
			i++;
		}
		cmd = cmd->next;
	}
}

void init_execution(t_cmd *cmd_list, t_env_data *ev)
{
	process_all_heredocs(cmd_list);
	int		fd[2];
	int		prev_fd;
	int		pid;
	int		status;
	int		saved_stdout;
	int		saved_stdin;
	t_cmd	*cmd;
	char	**envp;

	saved_stdout = dup(STDOUT_FILENO);
	saved_stdin = dup(STDIN_FILENO);
	if (saved_stdout == -1 || saved_stdin == -1)
	{
		perror("minishell: dup error");
		exit(EXIT_FAILURE);
	}
	prev_fd = -1;
	cmd = cmd_list;
	envp = env_list_to_envp(ev->env_list);
	while (cmd)
	{
		// Handle pipes
		if (cmd && cmd->next)
		{
			if (pipe(fd) == -1)
			{
				perror("pipe error");
				exit(EXIT_FAILURE);
			}
		}
		// Initialize arguments
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
		// Parse arguments
		while (cmd->args[i])
		{
			if (ft_strcmp(cmd->args[i], ">") == 0 || ft_strcmp(cmd->args[i], ">>") == 0)
			{
				int tmp_fd;
				int is_append = ft_strcmp(cmd->args[i], ">>") == 0;

				// tmp_fd = open(cmd->args[i + 1],
				// 	O_WRONLY | O_CREAT | (is_append ? O_APPEND : O_TRUNC), 0644);
				tmp_fd = handle_redirection(cmd->args[i + 1], is_append);
				if (tmp_fd == 1)
					perror("minishell: redirection error");
				// else
				// 	close(tmp_fd); // Just ensure file is created

				// Store only the last redirection
				if (cmd->outfile)
					free(cmd->outfile);
				cmd->outfile = strdup(cmd->args[i + 1]);
				cmd->append_fd = is_append;
				i++;
			}
			// if (ft_strcmp(cmd->args[i], ">") == 0 || ft_strcmp(cmd->args[i], ">>") == 0)
			// {
			// 	cmd->outfile = strdup(cmd->args[i + 1]); // Saving output file
			// 	if (!cmd->outfile)
			// 		exit(EXIT_FAILURE);
			// 	cmd->append_fd = (ft_strcmp(cmd->args[i], ">>") == 0);
			// 	i++;
			// }
			else if (ft_strcmp(cmd->args[i], "<") == 0)
			{
				cmd->inputfile = strdup(cmd->args[i + 1]); // Saving input file
				if (!cmd->inputfile)
					exit(EXIT_FAILURE);
				i++;
			}
			else if (ft_strcmp(cmd->args[i], "<<") == 0)
				i++;
			else
				cmd->args_for_cmd[j++] = strdup(cmd->args[i]);
			i++;
		}
		cmd->args_for_cmd[j] = NULL;
		// Apply redirections for built-ins before execution
		if (cmd->cmd_type == TOKEN_BUILTIN)
			handle_builtin(cmd, ev, fd, &prev_fd);
		else
		{
			pid = fork();
			if (pid == 0) // Child process
			{
				if (cmd->inputfile)
					handle_input_redirection(cmd->inputfile);
				if (cmd->has_heredoc && cmd->heredoc_path)
					handle_heredoc(cmd->heredoc_path);
				if (cmd->outfile)
					handle_redirection(cmd->outfile, cmd->append_fd);
				
				if (!cmd->inputfile && !(cmd->has_heredoc && cmd->heredoc_path) && prev_fd != -1)
				{
					dup2(prev_fd, STDIN_FILENO);
					close(prev_fd);
				}
					
				// Redirect previous command's output to current command's input
				// if (prev_fd != -1)
				// {
				// 	dup2(prev_fd, STDIN_FILENO);
				// 	close(prev_fd); // FIX: Close previous pipe read end in child
				// }

				// Redirect current command's output to pipe
				// if (cmd->next)
				// {
				// 	dup2(fd[1], STDOUT_FILENO);
				// 	close(fd[1]); // FIX: Close write end of pipe in child
				// 	close(fd[0]); // FIX: Close read end of pipe in child
				// }
				// Only redirect to pipe if there is NO explicit file redirection
				if (cmd->next && !cmd->outfile && !(cmd->has_heredoc && cmd->heredoc_path))
				{
					dup2(fd[1], STDOUT_FILENO);
					close(fd[1]);
					close(fd[0]);
				}


				execute_command(cmd, envp);
				exit(EXIT_FAILURE); // Just in case
			}
			else if (pid == -1)
			{
				perror("fork error");
				exit(EXIT_FAILURE);
			}
			
		}
		
		// Parent process
		if (prev_fd != -1)
			close(prev_fd); // Close previous read end in the parent
		if (cmd->next)
		{
			close(fd[1]); // Close write end in parent to signal EOF to next command
			prev_fd = fd[0]; // Pass read end to next command
		}
		cmd = cmd->next;
	}
	// Wait for all child processes
	while (wait(&status) > 0);
	if (cmd && cmd_list->cmd_type != TOKEN_BUILTIN)
		ev->last_exit = WEXITSTATUS(status);
	// Restore standard input and output
	if (dup2(saved_stdout, STDOUT_FILENO) == -1 || dup2(saved_stdin, STDIN_FILENO) == -1)
	{
		perror("minishell: dup2 error");
		exit(EXIT_FAILURE);
	}
	close(saved_stdout);
	close(saved_stdin);
}



