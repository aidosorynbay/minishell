/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorynbay <@student.42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 10:55:20 by mohkhan           #+#    #+#             */
/*   Updated: 2025/03/11 13:41:58 by aorynbay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_exit(char **args)
{
    int exit_code;

    exit_code = 0;
    if (args[1])
        exit_code = ft_atoi(args[1]);
    exit(exit_code);
    return 1;
}
