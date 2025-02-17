#include "minishell.h"

static void handle_builtin(t_cmd *cmd)
{
    fprintf(stderr, "---------------*************----------------\n");
    if (!cmd || !cmd->args || !cmd->args[0])
        return;
    fprintf(stderr, "Executing builtin command: %s\n", cmd->args[0]);
    
    for (int i = 1; cmd->args[i]; i++)
        fprintf(stderr, "Arg[%d]: %s\n", i, cmd->args[i]);

    if (strcmp(cmd->args[0], "echo") == 0)
        ft_echo(cmd->args);
    else if (strcmp(cmd->args[0], "cd") == 0)
        ft_cd(cmd->args);
    else if (strcmp(cmd->args[0], "exit") == 0)
        ft_exit(cmd->args);
    else if (strcmp(cmd->args[0], "pwd") == 0)
        ft_pwd();
    else
        fprintf(stderr, "Command not found: %s\n", cmd->args[0]);
    fprintf(stderr, "---------------*************----------------\n");
}

void handle_redirection(char *outfile, int append)
{
    fprintf(stderr, "---------------*************----------------\n");
    int fd;

    fprintf(stderr, "FOR DEBUGGING: Entering handle_redirection with outfile = %s, append = %d\n", outfile, append);
    if (outfile)
    {
        fprintf(stderr, "-----------------------\n");
        fprintf(stderr, "ENTERED REDIRECTION\n");
        if (append)
        {
            fprintf(stderr, "entered append mode\n");
            fd = open(outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
        }
        else
        {
            printf("entered truncate mode\n");
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
    // dup2(saved_stdout, STDOUT_FILENO);
    // close(saved_stdout);
    fprintf(stderr, "---------------*************----------------\n");
}

// void init_execution(t_cmd *cmd_list)
// {
//     t_cmd *cmd = cmd_list;

//     while (cmd)
//     {
//         printf("Executing command: %d\n", cmd->cmd_type);

//         if (cmd->cmd_type == TOKEN_BUILTIN)
//         {
//             printf("Executing built-in command: %s\n", cmd->args[0]);
//             handle_builtin(cmd);
//         }
//         else if (cmd->cmd_type == TOKEN_REDIRECT_OUT || cmd->cmd_type == TOKEN_REDIRECT_APPEND ||
//                  cmd->cmd_type == TOKEN_REDIRECT_IN || cmd->cmd_type == TOKEN_HEREDOC)
//         {
//             printf("Handling redirection\n");
//             handle_redirection(cmd->args[1], cmd->cmd_type);
//         }
//         else
//         {
//             // execute_external_command(cmd);
//             printf("Executing external command: %s\n", cmd->args[0]);
//         }
//         cmd = cmd->next;
//     }
// }


void init_execution(t_cmd *cmd_list)
{
    fprintf(stderr, "---------------*************----------------\n");
    t_cmd *cmd = cmd_list;
    int saved_stdout = dup(STDOUT_FILENO);
    int saved_stdin = dup(STDIN_FILENO);
    while (cmd)
    {
        int i = 0;
        fprintf(stderr, "Executing command: %d\n", cmd->cmd_type);
        while (cmd->args[i])
        {
            fprintf(stderr, "checking for redirection\n");
            if (strcmp(cmd->args[i], ">") == 0 || strcmp(cmd->args[i], ">>") == 0)
            {
                fprintf(stderr, "entering redirection\n");
                if (strcmp(cmd->args[i], ">") == 0)
                {
                    fprintf(stderr, "entered truncate mode\n");
                    handle_redirection(cmd->args[i + 1], 0);
                }
                else
                {
                    fprintf(stderr, "entered append mode\n");
                    handle_redirection(cmd->args[i + 1], 1);
                }
                i++;
            }
            else
            {
                fprintf(stderr, "*******Args are: %s*********\n", cmd->args[i]);
                i++;
            }
        }
        if (cmd->cmd_type == TOKEN_BUILTIN)
        {
            fprintf(stderr, "*******entered builtin*****\n");
            handle_builtin(cmd);
        }
        // else
        //     execute_command(cmd);
        cmd = cmd->next;
    }
    if ( dup2(saved_stdout, STDOUT_FILENO) == -1)
        perror("minishell: dup2 error");
    if (dup2(saved_stdin, STDIN_FILENO) == -1)
        perror("minishell: dup2 error");
    close(saved_stdout);
    close(saved_stdin);
    fprintf(stderr, "---------------*************----------------\n");
}

