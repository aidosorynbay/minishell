#include "minishell.h"

int count_args_for_cmd(char **tokens)
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

void	execute_builtin(t_cmd *cmd, t_env_data *ev)
{
	if (ft_strcmp(cmd->args[0], "echo") == 0)
		ft_echo(cmd->args_for_cmd);
	else if (ft_strcmp(cmd->args[0], "pwd") == 0)
		ft_pwd();
	else if (ft_strcmp(cmd->args[0], "env") == 0)
		ft_env(ev->env_list);
	else if (ft_strcmp(cmd->args[0], "export") == 0)
		ft_export(ev, cmd->args_for_cmd);
	// else if (ft_strcmp(cmd->args[0], "unset") == 0)
	// 	ft_unset(ev, cmd->args_for_cmd);
	else if (ft_strcmp(cmd->args[0], "exit") == 0)
		ft_exit(cmd->args_for_cmd);
	else
		perror("minishell: command not found");
}

void	free_args(char **args)
{
	int i = 0;
	while (args && args[i])
		free(args[i++]);
	free(args);
}