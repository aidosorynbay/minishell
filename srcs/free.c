#include "minishell.h"

void	free_tokens(char **tokens)
{
    int i = 0;

    if (!tokens)
        return;

    while (tokens[i])
    {
        free(tokens[i]);
        i++;
    }
    free(tokens);
    tokens = NULL;
}

void free_cmd_list(t_cmd *cmd_list)
{
    t_cmd *temp;

    while (cmd_list)
    {
        temp = cmd_list;
        cmd_list = cmd_list->next;

        // Free inputfile and outfile
        // if (temp->inputfile)
        //     free(temp->inputfile);
        // if (temp->outfile)
        //     free(temp->outfile);

        // Free args_for_cmd
        if (temp->args_for_cmd)
        {
            int i = 0;
            while (temp->args_for_cmd[i])
            {
                free(temp->args_for_cmd[i]);
                i++;
            }
            free(temp->args_for_cmd);
        }

        // Free args
        if (temp->args)
        {
            int i = 0;
            while (temp->args[i])
            {
                free(temp->args[i]);
                i++;
            }
            free(temp->args);
        }

        // Free the command node itself
        free(temp);
    }
}

void free_args(char **args)
{
    int i = 0;

    if (!args)
        return;

    while (args[i])
    {
        free(args[i]);
        i++;
    }
    free(args);
    args = NULL;
}

void	free_env_list(t_env *env_list)
{
	t_env	*temp;

	while (env_list)
	{
		temp = env_list;
		env_list = env_list->next;
		free(temp->key);
        temp->key = NULL;
		free(temp->value);
        temp->value = NULL;
		free(temp);
        temp = NULL;
	}
}

void	free_env_data(t_env_data *env_data)
{
    if (!env_data)
    return;
    free_env_list(env_data->env_list);
    env_data->env_list = NULL;
    free_env_list(env_data->env_export_list);
    env_data->env_export_list = NULL;
    free(env_data);
    env_data = NULL;
}

void free_cmd_data(t_cmd *cmd, t_env_data *ev)
{
    if (!cmd)
        return;
    if (cmd->envp)
    {
        free_args(cmd->envp);
        cmd->envp = NULL;
    }
    free(cmd->inputfile);
    cmd->inputfile = NULL;
    free(cmd->outfile);
    cmd->outfile = NULL;
    free(cmd->heredoc_path);
    cmd->heredoc_path = NULL;
    free_args(cmd->args_for_cmd);
    cmd->args_for_cmd = NULL;
    free_args(cmd->args);
    cmd->args = NULL;
    if (ev)
    {
        free_env_data(ev);
        ev = NULL;
    }
}

void	free_cmd(t_cmd *cmd, int fd[4])
{
	int	i;

	if (!cmd)
		return;
	if (cmd->args)
	{
		i = 0;
		while (cmd->args[i])
			free(cmd->args[i++]); // Only if you strdup args
		free(cmd->args);
	}
    if(cmd->args_for_cmd)
        free_args(cmd->args_for_cmd);
    if(cmd->envp)
    {
        i = 0;
        while (cmd->envp[i])
            free(cmd->envp[i++]);
        free(cmd->envp);
    }
    close(fd[2]);
    close(fd[3]);
	free(cmd);
}