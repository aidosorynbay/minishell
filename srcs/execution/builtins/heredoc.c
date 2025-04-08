#include "minishell.h"

void handle_heredoc(char *heredoc_path)
{
	int fd;

    if (heredoc_path)
	{
		fd = open(heredoc_path, O_RDONLY);
		if (fd == -1)
		{
			perror("open crashed");
			return;
		}
		dup2(fd, STDIN_FILENO);
		close(fd);
	}

}

char *ft_heredoc(char *limiter)
{
	int		fd;
	char	*line;
	char	*filename = "/tmp/.minishell_heredoc_tmp";

	fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror("heredoc open");
		return (NULL);
	}
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, limiter) == 0)
		{
			free(line);
			break;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	close(fd);
	return (ft_strdup(filename));
}
