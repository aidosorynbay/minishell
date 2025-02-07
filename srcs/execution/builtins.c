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

static char *find_executable(char *args)
{
    (void)args;
    return("/bin/ls");
}

void execute_command(char **args)
{
    char *cmd_path = find_executable(args[0]); // Find full path
    if (!cmd_path)
    {
        fprintf(stderr, "Command not found: %s\n", args[0]);
        exit(127);
    }
    execve(cmd_path, args, NULL);
    perror("execve failed"); // If execve fails
    exit(1);
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


