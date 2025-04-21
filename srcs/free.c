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

static	void	cmd_list_free_utils(t_cmd *cmd_list)
{
	if (cmd_list->heredoc_path)
	{
		free(cmd_list->heredoc_path);
		cmd_list->heredoc_path = NULL;
	}
	if (cmd_list->inputfile)
	{
		free(cmd_list->inputfile);
		cmd_list->inputfile = NULL;
	}
	if (cmd_list->outfile)
	{
		free(cmd_list->outfile);
		cmd_list->outfile = NULL;
	}
}

void	free_cmd_list(t_cmd *cmd_list)
{
	t_cmd	*temp;

	while (cmd_list)
	{
		temp = cmd_list;
		cmd_list = cmd_list->next;
		if (temp->args_for_cmd)
		{
			free_args(temp->args_for_cmd);
			temp->args_for_cmd = NULL;
		}
		if (temp->args)
		{
			free_args(temp->args);
			temp->args = NULL;
		}
		cmd_list_free_utils(temp);
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
			free_args(temp->envp);
		free(temp->inputfile);
		free(temp->outfile);
		free(temp->heredoc_path);
		free_args(temp->args_for_cmd);
		free_args(temp->args);
		cmd = cmd->next;
		free(temp);
	}
	if (ev)
		free_env_data(ev);
}
