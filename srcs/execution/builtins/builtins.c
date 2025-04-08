/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorynbay <@student.42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 10:53:29 by mohkhan           #+#    #+#             */
/*   Updated: 2025/04/08 21:20:34 by aorynbay         ###   ########.fr       */
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

void handle_redirection(char *outfile, int append)
{
	int fd;

	if (outfile)
	{
		if (append)
			fd = open(outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
			fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
			return(perror("minishell: redirection error"), (void)0);
		if(dup2(fd, STDOUT_FILENO) == -1)
			perror("DUP2 DUPPPED"); // Redirect stdout to file 
		close(fd);
	}
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
	pid_t pid;

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
				ft_echo(cmd->args_for_cmd);
			else if (ft_strcmp(cmd->args[0], "pwd") == 0)
				ft_pwd();
			else if (ft_strcmp(cmd->args[0], "env") == 0)
				ft_env(ev->env_list);
			else if (ft_strcmp(cmd->args[0], "export") == 0)
				ft_export(ev, cmd->args_for_cmd);
			exit(EXIT_SUCCESS);
		}
		waitpid(pid, NULL, 0); // Parent waits for child
		return;
	}
	else
	{
			// Execute normally if not in a pipeline
		if (ft_strcmp(cmd->args[0], "echo") == 0)
			ft_echo(cmd->args_for_cmd);
		else if (ft_strcmp(cmd->args[0], "pwd") == 0)
			ft_pwd();
		else if (ft_strcmp(cmd->args[0], "env") == 0)
			ft_env(ev->env_list);
		else if (ft_strcmp(cmd->args[0], "export") == 0)
			ft_export(ev, cmd->args_for_cmd);
	}
	
}



void init_execution(t_cmd *cmd_list, t_env_data *ev)
{
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
		if (cmd->next)
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
				cmd->outfile = strdup(cmd->args[i + 1]); // Saving output file
				if (!cmd->outfile)
					exit(EXIT_FAILURE);
				cmd->append_fd = (ft_strcmp(cmd->args[i], ">>") == 0);
				i++;
			}
			else if (ft_strcmp(cmd->args[i], "<") == 0)
			{
				cmd->inputfile = strdup(cmd->args[i + 1]); // Saving input file
				if (!cmd->inputfile)
					exit(EXIT_FAILURE);
				i++;
			}
			else
				cmd->args_for_cmd[j++] = strdup(cmd->args[i]);
			i++;
		}
		cmd->args_for_cmd[j] = NULL;
		// Apply redirections for built-ins before execution
		if (cmd->cmd_type == TOKEN_BUILTIN)
		{
			// if (cmd->inputfile)
			// 	handle_input_redirection(cmd->inputfile);
			// if (cmd->outfile)
			// 	handle_redirection(cmd->outfile, cmd->append_fd);
			handle_builtin(cmd, ev, fd, &prev_fd);
		}
		else
		{
			pid = fork();
			if (pid == 0) // Child process
			{
				if (cmd->inputfile)
					handle_input_redirection(cmd->inputfile);

				if (cmd->outfile)
				{
					if (cmd->append_fd)
						handle_redirection(cmd->outfile, 1);
					else
						handle_redirection(cmd->outfile, 0);
				}

				// Redirect previous command's output to current command's input
				if (prev_fd != -1)
				{
					dup2(prev_fd, STDIN_FILENO);
					close(prev_fd); // FIX: Close previous pipe read end in child
				}

				// Redirect current command's output to pipe
				if (cmd->next)
				{
					dup2(fd[1], STDOUT_FILENO);
					close(fd[1]); // FIX: Close write end of pipe in child
					close(fd[0]); // FIX: Close read end of pipe in child
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



