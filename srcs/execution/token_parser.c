#include "minishell.h"


static t_cmd *create_cmd()
{
	t_cmd *cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!cmd)
	{
		perror("malloc");
		// free_all(tokens, cmd);
		exit(1);
	}
	cmd->args = NULL;
	cmd->input_fd = STDIN_FILENO;  // Default input is stdin
	cmd->output_fd = STDOUT_FILENO; // Default output is stdout
	cmd->next = NULL;
	return cmd;
}

static void add_arg_to_cmd(t_cmd *cmd, char *arg)
{
	int count;
	int i;
	
	i = 0;
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

t_cmd *parse_tokens(t_token **tokens)
{
	t_cmd *head;
	t_cmd *current;
	t_token *tmp;
	int i;
	
	tmp = *tokens;
	head = NULL;
	current = NULL;
	i = 0;

	while (tmp->next != NULL)
	{
		if (!head)
		{
			head = create_cmd();
			current = head;
		}
		else if (strcmp(tmp->value, "|") == 0)
		{
			current->next = create_cmd();
			current = current->next;
			i++;
		}
		else if (strcmp(tmp->value, "<") == 0)
		{
			current->input_fd = open(tmp -> next -> next, O_RDONLY);
			tmp = tmp -> next -> next;
		}
		else if (strcmp(tmp->value, ">") == 0)
		{
			current->output_fd = open(tmp -> next -> next, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			tmp = tmp -> next -> next;
		}
		else if (strcmp(tmp->value, ">>") == 0)
		{
			current->output_fd = open(tmp->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
			tmp = tmp -> next -> next;
		}
		else
		{
			add_arg_to_cmd(current, tmp->value);
			tmp = tmp ->next;
		}
	}
	return head;
}
