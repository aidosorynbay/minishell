/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohkhan <mohkhan@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 12:20:10 by mohkhan           #+#    #+#             */
/*   Updated: 2025/04/21 12:20:11 by mohkhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_cmd_list(t_cmd *cmd_list)
{
	t_cmd	*temp;

	while (cmd_list)
	{
		temp = cmd_list;
		cmd_list = cmd_list->next;
		if (temp->args_for_cmd)
			free_args(temp->args_for_cmd);
		if (temp->args)
			free_args(temp->args);
		if (temp->heredoc_path)
		{
			free(temp->heredoc_path);
			temp->heredoc_path = NULL;
		}
		if (temp->inputfile)
		{
			free(temp->inputfile);
			temp->inputfile = NULL;
		}
		if (temp->outfile)
		{
			free(temp->outfile);
			temp->outfile = NULL;
		}
		free(temp);
	}
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
		return ;
	free_env_list(env_data->env_list);
	env_data->env_list = NULL;
	free_env_list(env_data->env_export_list);
	env_data->env_export_list = NULL;
	free(env_data);
	env_data = NULL;
}

void	free_cmd_data(t_cmd *cmd, t_env_data *ev)
{
	t_cmd	*temp;

	if (!cmd)
		return ;
	while (cmd)
	{
		temp = cmd;
		if (temp->envp)
		{
			free_args(temp->envp);
			// temp->envp = NULL;
		}
		free(temp->inputfile);
		// temp->inputfile = NULL;
		free(temp->outfile);
		// temp->outfile = NULL;
		free(temp->heredoc_path);
		// temp->heredoc_path = NULL;
		free_args(temp->args_for_cmd);
		// temp->args_for_cmd = NULL;
		free_args(temp->args);
		// temp->args = NULL;
		cmd = cmd->next;
		free(temp);
	}
	if (ev)
	{
		free_env_data(ev);
		// ev = NULL;
	}
}

void	free_cmd(t_cmd *cmd, int fd[4])
{
	if (!cmd)
		return ;
	if (cmd->args)
		free_args(cmd->args);
	if (cmd->args_for_cmd)
		free_args(cmd->args_for_cmd);
	if (cmd->envp)
		free_args(cmd->envp);
	close(fd[2]);
	close(fd[3]);
	free(cmd);
}
