/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorynbay <@student.42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 10:55:20 by mohkhan           #+#    #+#             */
/*   Updated: 2025/04/14 20:32:37 by aorynbay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_exit(char **args)
{
    int exit_code = 0;

    // Print exit message
    ft_putstr_fd("exit\n", STDERR_FILENO);

    // No arguments: exit with code 0
    if (!args[1])
        exit(exit_code);

    // Check if the first argument is numeric
    int i = 0;
    while (args[1][i])
    {
        if (!ft_isdigit(args[1][i]) && !(i == 0 && (args[1][i] == '-' || args[1][i] == '+')))
        {
            ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
            ft_putstr_fd(args[1], STDERR_FILENO);
            ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
            exit(255); // Exit with code 255 for invalid numeric argument
        }
        i++;
    }

    // Convert the first argument to an integer
    exit_code = ft_atoi(args[1]);

    // Check for multiple arguments
    if (args[2])
    {
        ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
        return (1); // Return 1 but do not exit the shell
    }

    // Exit with the parsed exit code
    exit(exit_code);
}
