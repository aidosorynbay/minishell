/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohkhan <mohkhan@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 12:53:56 by aorynbay          #+#    #+#             */
/*   Updated: 2025/04/21 13:26:27 by mohkhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_env(t_env *ev)
{
    if (!ev)
    {
        perror("minishell: env: No environment variables found\n");
        return (1);
    }
    while (ev)
	{
		printf("%s=%s\n", ev->key, ev->value);
		ev = ev->next;
	}
    return (0);
}
