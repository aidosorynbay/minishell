#include "minishell.h"

void	allocate_args_for_cmd(t_cmd *cmd)
{
	cmd->count_cmd = count_args_for_cmd(cmd->args);
	if (cmd->count_cmd > 0)
	{
		cmd->args_for_cmd = malloc(sizeof(char *) * (cmd->count_cmd + 1));
		if (!cmd->args_for_cmd)
		{
			perror("malloc failed");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		cmd->args_for_cmd = NULL;
	}
}
