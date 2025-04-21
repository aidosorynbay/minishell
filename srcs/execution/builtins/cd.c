/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohkhan <mohkhan@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 10:54:08 by mohkhan           #+#    #+#             */
/*   Updated: 2025/04/21 12:40:35 by mohkhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int	check_tilda(char **args, char *home_path, char *new_path)
{
	home_path = getenv("HOME");
	if (!home_path)
		return (1);
	new_path = malloc(strlen(home_path) + ft_strlen(args[1]));
	if (!new_path)
		return (1);
	ft_strcpy(new_path, home_path);
	ft_strcat(new_path, args[1] + 1);
	if (chdir(new_path) == -1)
	{
		perror("cd");
		free(new_path);
		return (1);
	}
	free(new_path);
	return (0);
}

int	ft_cd(char **args)
{
	char	*home_path;
	char	*new_path;
	int		check;

	home_path = NULL;
	new_path = NULL;
	if (!args || !args[1])
	{
		home_path = getenv("HOME");
		if (!home_path)
			return (1);
		if (chdir(home_path) == -1)
			return (perror("cd"), 1);
		return (0);
	}
	if (args[1][0] == '~')
	{
		check = check_tilda(args, home_path, new_path);
		return (check);
	}
	if (chdir(args[1]) == -1)
		return (perror("cd"), 1);
	return (0);
}
