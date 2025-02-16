#include "minishell.h"

static void handle_builtin(t_cmd *cmd)
{
    if (!cmd || !cmd->args || !cmd->args[0])
        return;

    printf("Executing builtin command: %s\n", cmd->args[0]);
    
    for (int i = 1; cmd->args[i]; i++)
        printf("Arg[%d]: %s\n", i, cmd->args[i]);

    if (strcmp(cmd->args[0], "echo") == 0)
        ft_echo(cmd->args);
    else if (strcmp(cmd->args[0], "cd") == 0)
        ft_cd(cmd->args);
    else if (strcmp(cmd->args[0], "exit") == 0)
        ft_exit(cmd->args);
    else if (strcmp(cmd->args[0], "pwd") == 0)
        ft_pwd();
    else
        printf("Command not found: %s\n", cmd->args[0]);
}

void handle_redirection(char *outfile, int append)
{
    int fd;

    if (outfile)
    {
        printf("-----------------------\n");
        printf("ENTERED REDIRECTION\n");
        if (append)
        {
            printf("entered append mode\n");
            fd = open(outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
        }
        else
        {
            printf("entered append mode\n");
            fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        }
        if (fd == -1)
        {
            perror("minishell: redirection error");
            return;
        }
        dup2(fd, STDOUT_FILENO); // Redirect stdout to file 
        close(fd);
    }
}

void init_execution(t_cmd *cmd_list)
{
    t_cmd *cmd = cmd_list;
    int saved_stdout = dup(STDOUT_FILENO);

    dup2(saved_stdout, STDOUT_FILENO);
    close(saved_stdout);
    while (cmd)
    {
        int i = 0;
        printf("Executing command: %d\n", cmd->cmd_type);
        while (cmd->args[i])
        {
            if (strcmp(cmd->args[i], ">") == 0 || strcmp(cmd->args[i], ">>") == 0)
            {
                printf("entering redirection\n");
                if (strcmp(cmd->args[i], ">"))
                    handle_redirection(cmd->args[i + 1], 0);
                else
                    handle_redirection(cmd->args[i + 1], 1);
            }
            printf("Arg: %s\n", *cmd->args);
            i++;
        }
        if (cmd->cmd_type == TOKEN_BUILTIN)
        {
            printf("entered builtin\n");
            handle_builtin(cmd);
        }
        // else
        //     execute_command(cmd);
        cmd = cmd->next;
    }
}

