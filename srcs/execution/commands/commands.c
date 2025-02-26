/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorynbay <@student.42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 18:36:58 by aorynbay          #+#    #+#             */
/*   Updated: 2025/02/26 17:41:57 by aorynbay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern char **environ; // Global environment variable

char *find_command_path(char *cmd, char **envp)
{
    int i;
    char *path;
    char *full_path;
    char *token;
    
    if (!cmd || !envp)
        return (NULL);
    if (access(cmd, X_OK) == 0) // If command is an absolute/relative path and executable
        return (strdup(cmd));
    i = 0;
    while (envp[i])
    {
        if (strncmp(envp[i], "PATH=", 5) == 0) // Find PATH variable in env
        {
            path = envp[i] + 5;
            token = strtok(path, ":");
            while (token)
            {
                full_path = malloc(strlen(token) + strlen(cmd) + 2);
                if (!full_path)
                    return (NULL);
                sprintf(full_path, "%s/%s", token, cmd);
                if (access(full_path, X_OK) == 0) // Check if executable
                    return (full_path);
                free(full_path);
                token = strtok(NULL, ":");
            }
        }
        i++;
    }
    return (NULL); // Command not found
}

void execute_command(t_cmd *cmd)
{
    char *cmd_path;

    if (!cmd || !cmd->args_for_cmd || !cmd->args_for_cmd[0])
    {
        fprintf(stderr, "minishell: command not found\n");
        exit(127);
    }
    
    cmd_path = find_command_path(cmd->args_for_cmd[0], environ);
    if (!cmd_path)
    {
        fprintf(stderr, "minishell: %s: command not found\n", cmd->args_for_cmd[0]);
        exit(127);
    }
    
    if (execve(cmd_path, cmd->args_for_cmd, environ) == -1)
    {
        perror("execve");
        free(cmd_path);
        if (errno == EACCES)
			exit(126); // Permission denied
		else
			exit(127); // Command not found

    }
}
