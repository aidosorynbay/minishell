#include "minishell.h"

void    clear_screen(void)
{
    write(STDOUT_FILENO, "\033[H\033[J", 6);
}

void free_all(t_token *tokens, t_cmd *cmd)
{
    token_clear(&tokens);
    while (cmd)
    {
        free(cmd->args);
        t_cmd *tmp = cmd;
        cmd = cmd->next;
        free(tmp);
    }
}