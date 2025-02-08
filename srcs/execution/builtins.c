#include "minishell.h"


// int builtin_cd(char **args)
// {
//     if (!args[1])
//     {
//         chdir(getenv("HOME"));
//         return 1;
//     }
//     else if (chdir(args[1]) == -1)
//     {
//         perror("cd");
//         return 0;
//     }
//     return 1;
// }

// int builtin_exit(char **args)
// {
//     if (args[1])
//     {
//         int exit_code = ft_atoi(args[1]);
//         exit(exit_code);
//     }
//     exit(0);
//     return 1;
// }

// int builtin_echo(char **args)
// {
//     int i = 1;
//     while (args[i])
//     {
//         ft_putstr_fd(args[i], 1);
//         if (args[i + 1])
//             write(1, " ", 1);
//         i++;
//     }
//     ft_putstr_fd("\n", 1);
//     return 1;
// }

// int handle_builtin(t_cmd *cmd)
// {
//     if (!cmd || !cmd->args || !cmd->args[0])
//         return 0;

//     if (cmd->cmd_type == TOKEN_BUILTIN)
//     {
//         if (strcmp(cmd->args[0], "cd") == 0)
//             return builtin_cd(cmd->args);
//         else if (strcmp(cmd->args[0], "exit") == 0)
//             return builtin_exit(cmd->args);
//         else if (strcmp(cmd->args[0], "echo") == 0)
//             return builtin_echo(cmd->args);
//     }
//     return 0;
// }

#include "minishell.h"

void ft_echo(t_token *args)
{
    t_token *current = args;

    while (current)
    {
        ft_putstr_fd(current->value, 1);
        if (current->next)
            ft_putchar_fd(' ' , 1);
        current = current->next;
    }
    ft_putchar_fd('\n', 1);
}
void    handle_builtin(t_cmd *cmd)
{
    if (!cmd || !cmd->args || !cmd->args[0])
        return;

    if (strcmp(cmd->args[0], "echo") == 0)
        ft_echo(cmd->args);
    else if (strcmp(cmd->args[0], "cd") == 0)
        ft_cd(cmd->args);
    else if (strcmp(cmd->args[0], "pwd") == 0)
        ft_pwd();
    else if (strcmp(cmd->args[0], "export") == 0)
        ft_export(cmd->args);
    else if (strcmp(cmd->args[0], "unset") == 0)
        ft_unset(cmd->args);
    else if (strcmp(cmd->args[0], "env") == 0)
        ft_env();
    else if (strcmp(cmd->args[0], "exit") == 0)
        ft_exit(cmd->args);
}

void execute_command(t_cmd *cmd)
{
    if (!cmd || !cmd->args || !cmd->args[0])
        return;

    if (is_builtin(cmd->args[0]))
        handle_builtin(cmd);
    else
        execute_external(cmd);
}



// void execute_commands(t_cmd *cmd_list)
// {
//     t_cmd *cmd = cmd_list;
//     while (cmd)
//     {
//         if (cmd->cmd_type == TOKEN_BUILTIN)
//             handle_builtin(cmd);
//         else
//             execute_command(cmd);
        
//         cmd = cmd->next;
//     }
// }


