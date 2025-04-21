/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorynbay <@student.42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 12:53:56 by aorynbay          #+#    #+#             */
/*   Updated: 2025/04/12 05:29:17 by aorynbay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_env *ev)
{
	if (!ev)
	{
		perror("minishell: env: No environment variables found\n");
		return (1);
	}
	while (ev)
	{
		ft_putstr_fd(ev->key, STDOUT_FILENO);
		ft_putstr_fd("=", STDOUT_FILENO);
		if (ev->has_value)
			ft_putstr_fd(ev->value, STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
		ev = ev->next;
	}
	return (0);
}
