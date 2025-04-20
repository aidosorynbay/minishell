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


int ft_exit(t_env_data *ev, t_cmd *cmd, int fd[4])
{
    int exit_code;
    int i;

    exit_code = 0;
    // Print exit message
    ft_putstr_fd("exit\n", 2);

    // No arguments: exit with code 0
    if (!cmd->args_for_cmd[1])
    {
        free_env_data(ev);
        free_cmd(cmd, fd);
        exit(exit_code);
    }

    // Check if the first argument is numeric
    i = 0;
    while (cmd->args_for_cmd[1][i])
    {
        if (!ft_isdigit(cmd->args_for_cmd[1][i]) && !(i == 0 && (cmd->args_for_cmd[1][i] == '-' || cmd->args_for_cmd[1][i] == '+')))
        {
            ft_putstr_fd("minishell: exit: ", 2);
            ft_putstr_fd(cmd->args_for_cmd[1], 2);
            ft_putstr_fd(": numeric argument required\n", 2);
            free_env_data(ev);
            free_cmd(cmd, fd);
            exit(255); // Exit with code 255 for invalid numeric argument
        }
        i++;
    }

    // Convert the first argument to an integer
    exit_code = ft_atoi(cmd->args_for_cmd[1]);

    // Check for multiple arguments
    if (cmd->args_for_cmd[2])
    {
        ft_putstr_fd("minishell: exit: too many arguments\n", 2);
        return (1); // Return 1 but do not exit the shell
    }
    free_env_data(ev);
    free_cmd(cmd, fd);
    // Exit with the parsed exit code
    exit(exit_code);
}
