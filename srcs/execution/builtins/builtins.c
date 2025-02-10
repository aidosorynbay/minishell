// #include "minishell.h"

// static void    handle_builtin(t_cmd *cmd)
// {
//     if (!cmd || !cmd->args || !cmd->args[0])
//         return;
//     char **array = cmd -> args;
//     if (strcmp(array[0], "echo") == 0)
//         ft_echo(array);
//     else if (strcmp(array[0], "cd") == 0)
//         ft_cd(array);
//     else if (strcmp(array[0], "exit") == 0)
//         ft_exit(array);
//     // else if (strcmp(array[0], "pwd") == 0)
//     //     ft_pwd();
//     // else if (strcmp(array[0], "export") == 0)
//     //     ft_export(cmd->(&args));
//     // else if (strcmp(array[0], "unset") == 0)
//     //     ft_unset(cmd->(&args));
//     // else if (strcmp(array[0], "env") == 0)
//     //     ft_env();
// }

// void init_execution(t_cmd *cmd_list)
// {
//     t_cmd *cmd = cmd_list;
//     while (cmd)
//     {
//         if (cmd->cmd_type == TOKEN_BUILTIN)
//             handle_builtin(cmd);
//         // else
//         //     execute_command(cmd);
//         cmd = cmd->next;
//     }
// }


