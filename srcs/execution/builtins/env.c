/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorynbay <@student.42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 12:53:56 by aorynbay          #+#    #+#             */
/*   Updated: 2025/04/10 08:22:26 by aorynbay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_env(t_env *ev)
{
    if (!ev)
    {
        perror("minishell: env: No environment variables found\n");
        return;
    }
    while (ev)
	{
		printf("%s=%s\n", ev->key, ev->value);
		ev = ev->next;
	}
    return ;
}