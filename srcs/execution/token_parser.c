#include "minishell.h"

static int count_args(char **tokens, int start)
{
    int count = 0;
    while (tokens[start] && strcmp(tokens[start], "|") != 0)
    {
        if (strcmp(tokens[start], ">") == 0 || strcmp(tokens[start], ">>") == 0 || strcmp(tokens[start], "<") == 0)
        {
            start += 2; // Skip redirection and its argument (filename)
            continue;
        }
        count++;
        start++;
    }
    return count;
}


t_cmd *parse_tokens(char **tokens)
{
    t_cmd *head = NULL;
    t_cmd *current = NULL;
    int i = 0;

    while (tokens[i])
    {
        t_cmd *new_cmd = malloc(sizeof(t_cmd));
        if (!new_cmd)
            return NULL;
        // int k = 0;
        // int l = 0;
        new_cmd->input_fd = STDIN_FILENO;
        new_cmd->output_fd = STDOUT_FILENO;
        new_cmd->cmd_type = TOKEN_UNKNOWN;
        new_cmd->next = NULL;

        int arg_count = count_args(tokens, i);
        new_cmd->args = malloc(sizeof(char *) * (arg_count + 1));
        if (!new_cmd->args)
            return NULL;
        new_cmd->args2 = malloc(sizeof(char *) * (arg_count + 1));
        if (!new_cmd->args2)
            return NULL;

        int j = 0;
        while (tokens[i] && strcmp(tokens[i], "|") != 0)
        {
            // fprintf(stderr, "------Creating new cmd args---------\n");
            // if (strcmp(tokens[l], ">") != 0 || strcmp(tokens[l], ">>") != 0 || strcmp(tokens[l], "<") != 0 || strcmp(tokens[l], "<<") != 0)
            //     l+=2;
            // else
            //     l++;
            // new_cmd->args2[k] = tokens[l];
            // fprintf(stderr, "args[%d]: %s\n", k, new_cmd->args[k]);
            // k++;
            // fprintf(stderr, "------Done creating new cmd args---------\n");
            if (strcmp(tokens[i], ">") == 0 || strcmp(tokens[i], ">>") == 0 || strcmp(tokens[i], "<") == 0 || strcmp(tokens[i], "<<") == 0)
            {
                if (strcmp(tokens[i], ">") == 0)
                    new_cmd->cmd_type = TOKEN_REDIRECT_OUT;
                else if (strcmp(tokens[i], ">>") == 0)
                    new_cmd->cmd_type = TOKEN_REDIRECT_APPEND;
                else if (strcmp(tokens[i], "<") == 0)
                    new_cmd->cmd_type = TOKEN_REDIRECT_IN;
                else if (strcmp(tokens[i], "<<") == 0)
                    new_cmd->cmd_type = TOKEN_REDIRECT_IN;
            }
            new_cmd->args[j] = tokens[i];
            i++;
            j++;
        }
        if (new_cmd->args[0] && (strcmp(new_cmd->args[0], "echo") == 0 ||
                                 strcmp(new_cmd->args[0], "cd") == 0 ||
                                 strcmp(new_cmd->args[0], "exit") == 0||
                                 strcmp(new_cmd->args[0], "pwd") == 0))
            new_cmd->cmd_type = TOKEN_BUILTIN;

        if (!head)
            head = new_cmd;
        else
            current->next = new_cmd;

        current = new_cmd;

        if (tokens[i] && strcmp(tokens[i], "|") == 0)
            i++;
    }
    return head;
}

