/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohkhan <mohkhan@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 10:55:11 by mohkhan           #+#    #+#             */
/*   Updated: 2025/02/22 10:55:13 by mohkhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int ft_echo(char **args)
// {
//     if (!args)
//         return (0);
//     if (!args[1])
//         return(0);
//     if (ft_strcmp(args[1], "-n") == 0)
//     {
//         int i = 2;
//         while (args[i] != NULL)
//         {
//             ft_putstr_fd(args[i], 1);
//             if (args[i + 1])
//                 write(1, " ", 1);
//             i++;
//         }
//     }
//     else
//     {
//         int i = 1;
//         while (args[i])
//         {
//             ft_putstr_fd(args[i], 1);
//             if (args[i + 1])
//                 write(1, " ", 1);
//             i++;
//         }
//         ft_putstr_fd("\n", 1);
//     }
//     return (1);
// }

int ft_echo(char **args)
{
    int i;
    int newline;

    i = 1;
    newline = 1;
    if (!args)
        return (0);
    while (args[i] && ft_strcmp(args[i], "-n") == 0) 
    {
        newline = 0;
        i++;
    }
    while (args[i])
    {
        ft_putstr_fd(args[i], 1);
        if (args[i + 1])
            write(1, " ", 1);
        i++;
    }
    if (newline)
        ft_putstr_fd("\n", 1);

    return (1);
}

