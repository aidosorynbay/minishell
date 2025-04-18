/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorynbay <@student.42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 10:55:20 by mohkhan           #+#    #+#             */
/*   Updated: 2025/04/18 15:25:18 by aorynbay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_cmd(t_cmd *cmd)
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
    if(cmd->envp)
    {
        i = 0;
        while (cmd->envp[i])
            free(cmd->envp[i++]);
        free(cmd->envp);
    }
	free(cmd);
}

int ft_exit(char **args, t_env_data *ev, t_cmd *cmd)
{
    int exit_code = 0;
    // (void)(cmd); // remove

    // Print exit message
    ft_putstr_fd("exit\n", 2);

    // No arguments: exit with code 0
    if (!args[1])
    {
        free_env_data(ev);
        free_args_for_cmd(args);
        free_cmd(cmd);
        exit(exit_code);
    }

    // Check if the first argument is numeric
    int i = 0;
    while (args[1][i])
    {
        if (!ft_isdigit(args[1][i]) && !(i == 0 && (args[1][i] == '-' || args[1][i] == '+')))
        {
            ft_putstr_fd("minishell: exit: ", 2);
            ft_putstr_fd(args[1], 2);
            ft_putstr_fd(": numeric argument required\n", 2);
            free_env_data(ev);
            free_args_for_cmd(args);
            // free_cmd_list(cmd);
            exit(255); // Exit with code 255 for invalid numeric argument
        }
        i++;
    }

    // Convert the first argument to an integer
    exit_code = ft_atoi(args[1]);

    // Check for multiple arguments
    if (args[2])
    {
        ft_putstr_fd("minishell: exit: too many arguments\n", 2);
        // free_env_data(ev);
        // free_args_for_cmd(args);
        // free_cmd_list(cmd);
        return (1); // Return 1 but do not exit the shell
    }
    free_env_data(ev);
    free_args_for_cmd(args);
    // free_cmd_list(cmd);
    // Exit with the parsed exit code
    exit(exit_code);
}
