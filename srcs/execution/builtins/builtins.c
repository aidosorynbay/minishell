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

void init_execution(t_cmd *cmd_list)
{
    t_cmd *cmd = cmd_list;
    while (cmd)
    {
        printf("Executing command: %d\n", cmd->cmd_type);
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


