/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohkhan <mohkhan@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 18:47:50 by mohkhan           #+#    #+#             */
/*   Updated: 2025/04/21 18:47:51 by mohkhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_redirection(char *outfile, int append)
{
	int	fd;

	if (outfile)
	{
		if (append)
			fd = open(outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
			fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
			return (1);
		if (dup2(fd, STDOUT_FILENO) == -1)
		{
			perror("DUP2 DUPPPED");
			return (1);
		}
		close(fd);
	}
	return (0);
}

int	open_fds(char *outfile, int append)
{
	int	fd;

	if (outfile)
	{
		if (append)
			fd = open(outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
			fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
			return (1);
		close(fd);
	}
	return (0);
}

int	handle_input_redirection(char *infile)
{
	int	fd;

	if (infile)
	{
		fd = open(infile, O_RDONLY);
		if (fd == -1)
			return (1);
		if (dup2(fd, STDIN_FILENO) == -1)
		{
			perror("Dup2 got dupped\n");
			return (1);
		}
		close(fd);
	}
	return (0);
}
