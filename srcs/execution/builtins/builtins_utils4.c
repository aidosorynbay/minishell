#include "minishell.h"

void	single_builtin(t_cmd *cmd, t_env_data *ev, int fd[4])
{
	implement_redir(cmd);
	execute_builtins(cmd, ev, fd);
}
