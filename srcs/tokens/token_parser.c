#include "minishell.h"


t_cmd *create_cmd() {
	t_cmd *cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!cmd)
	{
		perror("malloc");
		exit(1);
	}
	cmd->args = NULL;
	cmd->input_fd = STDIN_FILENO;  // Default input is stdin
	cmd->output_fd = STDOUT_FILENO; // Default output is stdout
	cmd->next = NULL;
	return cmd;
}

void add_arg_to_cmd(t_cmd *cmd, char *arg)
{
	int count;
	
	count = 0;
	if (cmd->args)
		while (cmd->args[count])
			count++;
	char **new_args = (char **)malloc((count + 2) * sizeof(char *));
	if (!new_args) {
		perror("malloc");
		exit(1);
	}
	i = -1;
	while(++i < count) 
		new_args[i] = cmd->args[i];
	new_args[count] = arg;
	new_args[count + 1] = NULL;
	if (cmd->args)
		free(cmd->args);
	cmd->args = new_args;
}

t_cmd *parse_tokens(char **tokens)
{
	t_cmd *head;
	t_cmd *current;
	int i;
	
	head = NULL;
	current = NULL;
	i = 0;
	while (tokens[i])
	{
		if (!head)
		{
			head = create_cmd();
			current = head;
		}
		else if (strcmp(tokens[i], "|") == 0)
		{
			current->next = create_cmd();
			current = current->next;
			i++;
		}
		else if (strcmp(tokens[i], "<") == 0)
		{
			current->input_fd = open(tokens[i + 1], O_RDONLY);
			i += 2;
		}
		else if (strcmp(tokens[i], ">") == 0)
		{
			current->output_fd = open(tokens[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
			i += 2;
		}
		else if (strcmp(tokens[i], ">>") == 0)
		{
			current->output_fd = open(tokens[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
			i += 2;
		}
		else
		{
			add_arg_to_cmd(current, tokens[i]);
			i++;
		}
	}
	return head;
}
