/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohkhan <mohkhan@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 10:55:29 by mohkhan           #+#    #+#             */
/*   Updated: 2025/02/22 10:55:44 by mohkhan          ###   ########.fr       */
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
