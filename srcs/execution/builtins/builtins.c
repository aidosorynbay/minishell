/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorynbay <@student.42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 10:53:29 by mohkhan           #+#    #+#             */
/*   Updated: 2025/04/02 18:23:52 by aorynbay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handler(t_cmd *cmd)
{
	if (cmd->inputfile)
		handle_input_redirection(cmd->inputfile);
	else if (cmd->heredoc_path)
		handle_heredoc(cmd->heredoc_path);
	if (cmd->outfile)
		handle_redirection(cmd->outfile, cmd->append_fd);
}
static void handle_builtin(t_cmd **cmd, t_env_data *ev, int fd[2], int *prev_fd)
{
	pid_t pid;

	if (!(*cmd) || !(*cmd)->args || !(*cmd)->args[0])
		return;
	// Always fork if part of a pipeline
	if ((*cmd)->next)
	{
		pid = fork();
		if (pid == -1)
		{
			perror("fork error");
			exit(EXIT_FAILURE);
		}
		if (pid == 0) // Child process
		{
			handler(*cmd);
			if (*prev_fd != -1)
			{
				dup2(*prev_fd, STDIN_FILENO);
				close(*prev_fd); // FIX: Close previous pipe read end in child
			}

			// Redirect current command's output to pipe
			if ((*cmd)->next)
			{
				dup2(fd[1], STDOUT_FILENO);
				close(fd[1]); // FIX: Close write end of pipe in child
				close(fd[0]); // FIX: Close read end of pipe in child
			}
			execute_builtin(*cmd, ev);
		}
		waitpid(pid, NULL, 0); // Parent waits for child
		return;
	}
	else
	{
		// int tmp_stdin = dup(STDIN_FILENO);
		// int tmp_stdout = dup(STDOUT_FILENO);

		handler(*cmd);
		execute_builtin((*cmd), ev);

		// dup2(tmp_stdin, STDIN_FILENO);
		// dup2(tmp_stdout, STDOUT_FILENO);
		// close(tmp_stdin);
		// close(tmp_stdout);
	}
}

void parse_arguments(t_cmd **cmd, int *i, int *j)
{
	while ((*cmd)->args[(*i)])
	{
		if (!ft_strcmp((*cmd)->args[(*i)], ">") || !ft_strcmp((*cmd)->args[(*i)], ">>"))
		{
			(*cmd)->outfile = strdup((*cmd)->args[(*i) + 1]); // Saving output file
			if (!(*cmd)->outfile)
				exit(EXIT_FAILURE);
			(*cmd)->append_fd = (!ft_strcmp((*cmd)->args[(*i)], ">>"));
			(*i)++;
		}
		else if (!ft_strcmp((*cmd)->args[(*i)], "<"))
		{
			(*cmd)->inputfile = strdup((*cmd)->args[(*i) + 1]); // Saving input file
			if (!(*cmd)->inputfile)
				exit(EXIT_FAILURE);
			(*i)++;
		}
		else if (!ft_strcmp((*cmd)->args[(*i)], "<<"))
			(*i)++;
		else
			(*cmd)->args_for_cmd[(*j)++] = strdup((*cmd)->args[(*i)]);
		(*i)++;
	}
	if ((*cmd)->args_for_cmd)
		(*cmd)->args_for_cmd[*j] = NULL;
}

void process_all_heredocs(t_cmd *cmd_list)
{
	t_cmd *cmd;
	int i;

	cmd = cmd_list;
	while (cmd)
	{
		i = 0;
		cmd->has_heredoc = 0;
		while (cmd->args && cmd->args[i])
		{
			if (!ft_strcmp(cmd->args[i], "<<"))
			{
				if (cmd->args[i + 1] == NULL)
				{
					fprintf(stderr, "minishell: syntax error near unexpected token `newline'\n");
					exit(EXIT_FAILURE);
				}
				// // Free previous heredoc path if set
				// if (cmd->heredoc_path)
				// {
				// 	free(cmd->heredoc_path);
				// 	cmd->heredoc_path = NULL;
				// }
				cmd->heredoc_path = ft_heredoc(cmd->args[i + 1]);
				if (!cmd->heredoc_path)
				{
					perror("heredoc processing failed");
					exit(EXIT_FAILURE);
				}
				cmd->has_heredoc = 1;
				i++; // Skip delimiter
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
	int		i;
	int		j;
	int		arg_count;
	t_cmd	*cmd;

	saved_stdout = dup(STDOUT_FILENO);
	saved_stdin = dup(STDIN_FILENO);
	prev_fd = -1;
	cmd = cmd_list;
	// cmd->args_for_cmd = NULL;
	cmd->heredoc_path = NULL;
	if (saved_stdout == -1 || saved_stdin == -1)
	{
		perror("minishell: dup error");
		exit(EXIT_FAILURE);
	}
	while (cmd)
	{
		// Handle pipes
		if (cmd->next && pipe(fd) == -1)
		{
			perror("pipe error");
			exit(EXIT_FAILURE);
		}
		// Initialize arguments
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
		parse_arguments(&cmd, &i, &j);

		// Apply redirections for built-ins before execution
		if (cmd->cmd_type == TOKEN_BUILTIN)
			handle_builtin(&cmd, ev, fd, &prev_fd);
		else
		{
			pid = fork();
			if (pid == 0) // Child process
			{
				handler(cmd);
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
				execute_command(cmd);
				exit(EXIT_FAILURE); // Just in case
			}
			else if (pid < 0)
			{
				perror("minishell: fork");
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
		// free_args(cmd->args_for_cmd);
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



