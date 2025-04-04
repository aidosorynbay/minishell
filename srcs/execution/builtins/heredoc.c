#include "minishell.h"
// #include <stdio.h>
// #include <stdlib.h>
// #include <unistd.h>
// #include <fcntl.h>
// #include <sys/wait.h>
// #include <readline/readline.h>
// #include <readline/history.h>

static int heredoc_count = 0;

static char *generate_tmpfile()
{
    char *filename = malloc(30);
    if (!filename)
        return NULL;
    sprintf(filename, "/tmp/minishell_heredoc_%d", heredoc_count++);
    return filename;
}

char *ft_heredoc(char *limiter, t_list **heredoc_list)
{
    int fd;
    char *line;
    char *tmpfile = generate_tmpfile();

    if (!tmpfile)
        return NULL;
    
    fd = open(tmpfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fd == -1)
    {
        perror("open");
        free(tmpfile);
        return NULL;
    }

    while (1)
    {
        line = readline("> ");
        if (!line || strcmp(line, limiter) == 0)  // Ctrl+D or EOF
        {
            free(line);
            break;
        }
        write(fd, line, strlen(line));
        write(fd, "\n", 1);
        free(line);
    }
    close(fd);
    
    // Store filename in linked list for cleanup later
    ft_lstadd_back(heredoc_list, ft_lstnew(ft_strdup(tmpfile)));

    return tmpfile;
}
