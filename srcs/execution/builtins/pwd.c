/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorynbay <@student.42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 10:55:29 by mohkhan           #+#    #+#             */
/*   Updated: 2025/04/02 16:34:40 by aorynbay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_pwd(void)
{
    char *cwd;
    int alloc;

    alloc = 1;
    cwd = getcwd(NULL, 0);
    if (!cwd)
    {
        cwd = getenv("PWD");
        alloc = 0;
    }
    if (cwd)
        ft_putendl_fd(cwd, 1);
    if (alloc)  
        free(cwd);
}
