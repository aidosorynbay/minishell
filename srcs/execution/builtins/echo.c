/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorynbay <@student.42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 10:55:11 by mohkhan           #+#    #+#             */
/*   Updated: 2025/04/10 21:06:05 by aorynbay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_echo(t_env_data *env_list, char **args)
{
	int i;
	int newline;

	i = 1;
	newline = 1;
	if (!args)
	{
		env_list->last_exit = 0;
		return (0);
	}
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
	env_list->last_exit = 0;
	return (1);
}

