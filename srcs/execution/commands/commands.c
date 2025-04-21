/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohkhan <mohkhan@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 18:36:58 by aorynbay          #+#    #+#             */
/*   Updated: 2025/04/21 18:46:45 by mohkhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/stat.h>

// extern char	**environ;

static char	*get_next_path(char *path, int *index)
{
	int		start;
	int		len;
	char	*token;

	while (path[*index] == ':')
		(*index)++;
	if (path[*index] == '\0')
		return (NULL);
	start = *index;
	len = find_char(path + start, ":");
	*index += len;
	token = malloc(len + 1);
	if (!token)
		return (NULL);
	ft_strncpy(token, path + start, len);
	token[len] = '\0';
	return (token);
}

static char	*build_command_path(const char *dir, const char *cmd)
{
	int		dir_len;
	int		cmd_len;
	char	*full_path;

	cmd_len = ft_strlen(cmd);
	dir_len = ft_strlen(dir);
	full_path = malloc(dir_len + cmd_len + 2);
	if (!full_path)
		return (NULL);
	ft_strcpy(full_path, dir);
	full_path[dir_len] = '/';
	ft_strcpy(full_path + dir_len + 1, cmd);
	return (full_path);
}

static char	*find_executable_in_path(const char *cmd, char *path)
{
	int		i;
	char	*dir;
	char	*full_path;

	i = 0;
	dir = get_next_path(path, &i);
	while (dir)
	{
		full_path = build_command_path(dir, cmd);
		free(dir);
		if (!full_path)
			return (NULL);
		if (access(full_path, X_OK) == 0)
			return (full_path);
		free(full_path);
		dir = get_next_path(path, &i);
	}
	return (NULL);
}

char	*find_command_path(char *cmd, char **envp)
{
	int		i;
	char	*path;

	i = 0;
	if (!cmd || !envp)
		return (NULL);
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
		else
			return (NULL);
	}
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	if (!envp[i])
		return (NULL);
	path = envp[i] + 5;
	return (find_executable_in_path(cmd, path));
}

static char	*handle_absolute_or_relative_path(t_cmd *cmd, t_env_data *ev)
{
	char	*cmd_path;

	if (access(cmd->args_for_cmd[0], F_OK) == -1)
	{
		fprintf(stderr, "minishell: %s: No such file or directory\n",
			cmd->args_for_cmd[0]);
		free_cmd_data(cmd, ev);
		exit(127);
	}
	if (access(cmd->args_for_cmd[0], X_OK) == -1)
	{
		fprintf(stderr, "minishell: %s: Permission denied\n",
			cmd->args_for_cmd[0]);
		free_cmd_data(cmd, ev);
		exit(126);
	}
	cmd_path = ft_strdup(cmd->args_for_cmd[0]);
	return (cmd_path);
}

static char	*handle_command_path(t_cmd *cmd, t_env_data *ev, char **environ)
{
	char	*cmd_path;

	if (cmd->args_for_cmd[0][0] == '/' || ft_strncmp(cmd->args_for_cmd[0], "./",
			2) == 0)
		cmd_path = handle_absolute_or_relative_path(cmd, ev);
	else
	{
		cmd_path = find_command_path(cmd->args_for_cmd[0], environ);
		if (!cmd_path)
		{
			fprintf(stderr, "minishell: %s: command not found\n",
				cmd->args_for_cmd[0]);
			free_cmd_data(cmd, ev);
			exit(127);
		}
	}
	return (cmd_path);
}

static void	free_exit(char *cmd_path, t_env_data *ev, t_cmd *cmd)
{
	fprintf(stderr, "minishell: %s: Is a directory\n", cmd_path);
	free_cmd_data(cmd, ev);
	free(cmd_path);
	exit(126);
}

void	execute_command(t_cmd *cmd, char **environ, t_env_data *ev)
{
	char		*cmd_path;
	struct stat	st;

	if (!cmd || !cmd->args_for_cmd || !cmd->args_for_cmd[0]
		|| !cmd->args_for_cmd[0][0])
	{
		fprintf(stderr, "minishell: command not found\n");
		free_cmd_data(cmd, ev);
		exit(127);
	}
	cmd_path = handle_command_path(cmd, ev, environ);
	if (!stat(cmd_path, &st) && S_ISDIR(st.st_mode))
		free_exit(cmd_path, ev, cmd);
	if (execve(cmd_path, cmd->args_for_cmd, environ) == -1)
	{
		perror("execve error");
		free(cmd_path);
		if (errno == EACCES)
			exit(126);
		else
			exit(127);
	}
	free(cmd_path);
	return ;
}
