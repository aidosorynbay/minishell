/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorynbay <@student.42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 10:53:29 by mohkhan           #+#    #+#             */
/*   Updated: 2025/03/19 01:32:48 by aorynbay         ###   ########.fr       */
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

static void handle_builtin(t_cmd *cmd, t_env_data *ev)
{
	fprintf(stderr, "---------------*************----------------\n");
	if (!cmd || !cmd->args || !cmd->args[0])
		return;
	fprintf(stderr, "Executing builtin command: %s\n", cmd->args[0]);
	for (int i = 1; cmd->args[i]; i++)
		fprintf(stderr, "Arg[%d]: %s\n", i, cmd->args[i]);
	if (ft_strcmp(cmd->args[0], "echo") == 0)
		ft_echo(cmd->args_for_cmd);
	else if (ft_strcmp(cmd->args[0], "cd") == 0)
		ft_cd(cmd->args_for_cmd);
	else if (ft_strcmp(cmd->args[0], "exit") == 0)
		ft_exit(cmd->args_for_cmd);
	else if (ft_strcmp(cmd->args[0], "pwd") == 0)
		ft_pwd();
	else if (ft_strcmp(cmd->args[0], "env") == 0)
		ft_env(ev);
	else if (ft_strcmp(cmd->args[0], "export") == 0)
		ft_export(ev, cmd->args_for_cmd);
	// else if (ft_strcmp(cmd->args[0], "unset") == 0)
	//     ft_unset(cmd->args_for_cmd, ev);
	else
		fprintf(stderr, "Command not found: %s\n", cmd->args[0]);
	fprintf(stderr, "---------------*************----------------\n");
}

void handle_redirection(char *outfile, int append)
{
	fprintf(stderr, "---------------*************----------------\n");
	int fd;

	if (outfile)
	{
		fprintf(stderr, "-----------------------\n");
		fprintf(stderr, "ENTERED REDIRECTION\n");
		if (append)
		{
			fprintf(stderr, "entered append mode\n");
			fd = open(outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
		}
		else
		{
			printf("entered truncate mode\n");
			fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		}
		if (fd == -1)
			return(perror("minishell: redirection error"), (void)0);
		if(dup2(fd, STDOUT_FILENO) == -1)
			perror("DUP2 DUPPPED"); // Redirect stdout to file 
		close(fd);
	}
	fprintf(stderr, "---------------*************----------------\n");
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

void init_execution(t_cmd *cmd_list, t_env_data *ev)
{
	int		fd[2];
	int		prev_fd;
	int		pid;
	int		status;
	int		saved_stdout;
	int		saved_stdin;
	t_cmd	*cmd;

	saved_stdout = dup(STDOUT_FILENO);
	saved_stdin = dup(STDIN_FILENO);
	if (saved_stdout == -1 || saved_stdin == -1)
	{
		perror("minishell: dup error");
		exit(EXIT_FAILURE);
	}

	prev_fd = -1;
	cmd = cmd_list;
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
		int i = 0, j = 0;
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
		int builtin_redir = 0;
		if (cmd->cmd_type == TOKEN_BUILTIN)
		{
			builtin_redir = 1;
			if (cmd->inputfile)
				handle_input_redirection(cmd->inputfile);
			if (cmd->outfile)
				handle_redirection(cmd->outfile, cmd->append_fd);
		}

		// Handle built-ins directly in the parent process
		if (cmd->cmd_type == TOKEN_BUILTIN)
		{
			handle_builtin(cmd, ev);
			if (builtin_redir)
			{
				if (dup2(saved_stdout, STDOUT_FILENO) == -1 || dup2(saved_stdin, STDIN_FILENO) == -1)
				{
					perror("minishell: dup2 error");
					exit(EXIT_FAILURE);
				}
			}
			cmd = cmd->next;
			continue;
		}

		// Fork for external commands
		pid = fork();
		if (pid == -1)
		{
			perror("fork error.");
			exit(EXIT_FAILURE);
		}

		if (pid == 0) // Child process
		{
			// Handle input redirection
			if (cmd->inputfile)
				handle_input_redirection(cmd->inputfile);

			// Handle output redirection
			if (cmd->outfile)
			{
				if (cmd->append_fd)
					handle_redirection(cmd->outfile, 1);
				else
					handle_redirection(cmd->outfile, 0);
			}

			// Pipe redirections
			if (prev_fd != -1)
			{
				dup2(prev_fd, STDIN_FILENO);
				close(prev_fd);
			}
			if (cmd->next)
			{
				dup2(fd[1], STDOUT_FILENO);
				close(fd[1]);
				close(fd[0]);
			}

			execute_command(cmd);
		}

		// Parent process
		if (prev_fd != -1)
			close(prev_fd);
		if (cmd->next)
		{
			close(fd[1]);
			prev_fd = fd[0];
		}

		cmd = cmd->next;
	}

	// Wait for all child processes
	while (wait(&status) > 0);

	// Restore standard input and output
	if (dup2(saved_stdout, STDOUT_FILENO) == -1 || dup2(saved_stdin, STDIN_FILENO) == -1)
	{
		perror("minishell: dup2 error");
		exit(EXIT_FAILURE);
	}
	close(saved_stdout);
	close(saved_stdin);
}



