/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorynbay <@student.42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 10:54:08 by mohkhan           #+#    #+#             */
/*   Updated: 2025/04/12 04:20:46 by aorynbay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
//incomplete ; fix the other cds too

int ft_cd(char **args)
{
    if (!args)
        return (1);
    if (!args[1])
    {
        chdir(getenv("HOME"));
        return (0);
    }
    else if (chdir(args[1]) == -1)
    {
        perror("cd");
        return 1;
    }
    return (0);
}
