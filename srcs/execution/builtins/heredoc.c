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
		if (dup2(fd, STDIN_FILENO) == -1)
		{
			perror("dup2 heredoc");
			exit(EXIT_FAILURE);
		}
		close(fd);
	}

}

// char *ft_heredoc(char *limiter)
// {
// 	int		fd;
// 	char	*line;
// 	char	*filename = "/tmp/.minishell_heredoc_tmp";

// 	fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
// 	if (fd < 0)
// 	{
// 		perror("heredoc open");
// 		return (NULL);
// 	}
// 	while (1)
// 	{
// 		line = readline("> ");
// 		if (!line || ft_strcmp(line, limiter) == 0)
// 		{
// 			free(line);
// 			break;
// 		}
// 		write(fd, line, ft_strlen(line));
// 		write(fd, "\n", 1);
// 		free(line);
// 	}
// 	close(fd);
// 	return (ft_strdup(filename));
// }


#include <signal.h>
#include <sys/wait.h>

int create_heredoc(char *limiter, char **heredoc_path)
{
    int pipe_fd[2];
    pid_t pid;
    int status;

    if (pipe(pipe_fd) == -1)
        return (perror("pipe"), -1);

    pid = fork();
    if (pid == -1)
        return (perror("fork"), -1);

    if (pid == 0)
    {
        signal(SIGINT, SIG_DFL);
        close(pipe_fd[0]);

        char *filename = "/tmp/.minishell_heredoc_tmp";
        int fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
        if (fd < 0)
            exit(1);

        char *line;
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
        write(pipe_fd[1], filename, strlen(filename) + 1);
        close(pipe_fd[1]);
        exit(0);
    }
    else
    {
        // Parent process
        close(pipe_fd[1]); // Close write end

        waitpid(pid, &status, 0);
        if (WIFSIGNALED(status) || WEXITSTATUS(status) != 0)
        {
            close(pipe_fd[0]);
            return (1); // heredoc was interrupted
        }

        char buffer[256];
        ssize_t n = read(pipe_fd[0], buffer, sizeof(buffer));
        if (n <= 0)
        {
            close(pipe_fd[0]);
            return (1);
        }
        *heredoc_path = ft_strdup(buffer);
        close(pipe_fd[0]);
        return (0);
    }
}
