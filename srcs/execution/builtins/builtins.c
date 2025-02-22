#include "minishell.h"

static int count_args_for_cmd(char **tokens)
{
    int count = 0;
    int start = 0;
    while (tokens[start] && ft_strcmp(tokens[start], "|") != 0 && 
       ft_strcmp(tokens[start], ">") != 0 && 
       ft_strcmp(tokens[start], ">>") != 0 && 
       ft_strcmp(tokens[start], "<") != 0)
    {
        count++;
        start++;
    }
    return count;
}

static void handle_builtin(t_cmd *cmd)
{
    fprintf(stderr, "---------------*************----------------\n");
    if (!cmd || !cmd->args || !cmd->args[0])
        return;
    fprintf(stderr, "Executing builtin command: %s\n", cmd->args[0]);
    
    for (int i = 1; cmd->args[i]; i++)
        fprintf(stderr, "Arg[%d]: %s\n", i, cmd->args[i]);

    if (ft_strcmp(cmd->args[0], "echo") == 0)
        ft_echo(cmd->args_for_cmd);
    else if (ft_strcmp(cmd->args[0], "cd") == 0)
        ft_cd(cmd->args_for_cmd);
    else if (ft_strcmp(cmd->args[0], "exit") == 0)
        ft_exit(cmd->args_for_cmd);
    else if (ft_strcmp(cmd->args[0], "pwd") == 0)
        ft_pwd();
    else
        fprintf(stderr, "Command not found: %s\n", cmd->args[0]);
    fprintf(stderr, "---------------*************----------------\n");
}

void handle_redirection(char *outfile, int append)
{
    fprintf(stderr, "---------------*************----------------\n");
    int fd;

    // fprintf(stderr, "FOR DEBUGGING: Entering handle_redirection with outfile = %s, append = %d\n", outfile, append);
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
        if(dup2(fd, STDOUT_FILENO) == -1)
            perror("DUP2 DUPPPED"); // Redirect stdout to file 
        close(fd);
    }
    fprintf(stderr, "---------------*************----------------\n");
}

void handle_input_redirection(char *infile)
{
    int fd;
    if (infile)
    {
        fd = open(infile, O_RDONLY);
        if (fd == -1)
        {
            perror("minishell: input redirection error");
            return ;
        }
        if (dup2(fd, STDIN_FILENO) == -1)
        {
            perror("Dup2 got dupped\n");
            return ;
        }
        close(fd);
    }   
}



void init_execution(t_cmd *cmd_list)
{
    fprintf(stderr, "---------------*************----------------\n");
    t_cmd *cmd = cmd_list;
    int saved_stdout = dup(STDOUT_FILENO);
    int saved_stdin = dup(STDIN_FILENO);
    int i;
    int j;
    
    while (cmd)
    {
        i = 0;
        j = 0;
        fprintf(stderr, "Executing command: %d\n", cmd->cmd_type);
        int arg_count = count_args_for_cmd(cmd->args);
        if (arg_count > 0)
        {
            cmd->args_for_cmd = malloc(sizeof(char *) * (arg_count + 1));
            if (!cmd->args_for_cmd)
            {
                perror("malloc failed");
                exit(1);
            }
        }
        else
            cmd->args_for_cmd = NULL;
        cmd->inputfile = NULL;
        cmd->outfile = NULL;
        while (cmd->args[i])
        {
            if (ft_strcmp(cmd->args[i], ">") == 0 || ft_strcmp(cmd->args[i], ">>") == 0)
            {
                cmd->outfile = strdup(cmd->args[i + 1]);  // Save output file
                if (!cmd->outfile)
                    return ;
                cmd->append_fd = (ft_strcmp(cmd->args[i], ">>") == 0);  // Set append flag
                i++;  // Skip file name
            }
            else if (ft_strcmp(cmd->args[i], "<") == 0)
            {
                cmd->inputfile = strdup(cmd->args[i + 1]);  // Save input file
                i++;  // Skip file name
            }
            // else if (ft_strcmp(cmd->args[i], "<<") == 0)
            // {
            //     cmd->heredoc = strdup(cmd->args[i + 1]);  // Save heredoc delimiter
            //     i++;  // Skip delimiter
            // }
            else
                cmd->args_for_cmd[j++] = strdup(cmd->args[i]);
            i++;
        }
        cmd->args_for_cmd[j] = NULL;  // Null-terminate

        fprintf(stderr, "checking for redirection\n");
        if (cmd->outfile || cmd-> inputfile)
        {
            fprintf(stderr, "entering redirection\n");
            if (cmd->inputfile)
            {
                handle_input_redirection(cmd->inputfile);
            }
            if (cmd->outfile && !cmd->append_fd)
            {
                fprintf(stderr, "entered truncate mode\n");
                handle_redirection(cmd->outfile, 0);
            }
            else if (cmd->outfile && cmd->append_fd)
            {
                fprintf(stderr, "entered append mode\n");
                handle_redirection(cmd->outfile, 1);
            }
        }
        if (cmd->cmd_type == TOKEN_BUILTIN)
        {
            fprintf(stderr, "*******entered builtin*****\n");
            handle_builtin(cmd);
        }
        else
            execute_command(cmd);
        cmd = cmd->next;
    }
    if (dup2(saved_stdout, STDOUT_FILENO) == -1)
        perror("minishell: dup2 error");
    if (dup2(saved_stdin, STDIN_FILENO) == -1)
        perror("minishell: dup2 error");
    close(saved_stdout);
    close(saved_stdin);
    fprintf(stderr, "---------------*************----------------\n");
}

