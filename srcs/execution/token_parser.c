#include "minishell.h"

static count_args(char **tokens, int start)
{
    int count = 0;
    while (tokens[start] && strcmp(tokens[start], "|") != 0)
    {
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
        if (!head)
        {
            head = malloc(sizeof(t_cmd));
            int arg_count = count_args(tokens, i);
            head->args = malloc(sizeof(char *) * (arg_count + 1));
            head->input_fd = STDIN_FILENO;
            head->output_fd = STDOUT_FILENO;
            head->next = NULL;
            current = head;
        }
        else if (strcmp(tokens[i], "|") == 0)
        {
            i++;
            current->next = malloc(sizeof(t_cmd));
            current = current->next;
            int arg_count = count_args(tokens, i);
            current->args = malloc(sizeof(char *) * (arg_count + 1));
            current->input_fd = STDIN_FILENO;
            current->output_fd = STDOUT_FILENO;
            current->next = NULL;
        }

        int j = 0;
        while (tokens[i] && strcmp(tokens[i], "|") != 0)
        {
            current->args[j] = strdup(tokens[i]);
            j++;
            i++;
        }
        current->args[j] = NULL;
    }
    return head;
}

