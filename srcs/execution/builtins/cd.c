/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohkhan <mohkhan@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 10:54:08 by mohkhan           #+#    #+#             */
/*   Updated: 2025/02/22 10:54:09 by mohkhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
//incomplete ; fix the other cds too

int ft_cd(char **args)
{
    if (!args)
        return 0;
    if (!args[1])
    {
        chdir(getenv("HOME"));
        return 1;
    }
    else if (chdir(args[1]) == -1)
    {
        perror("cd");
        return 0;
    }
    return 1;
}
