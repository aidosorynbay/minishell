#include "minishell.h"

#include <stdio.h>
#include <string.h>
#include "minishell.h"

void check_syntax(t_token *tokens)
{
    t_token *curr = tokens;
    t_token *prev = NULL;

    while (curr)
    {
        // Check for consecutive pipes
        if (curr->type == TOKEN_OPERATOR && curr->value[0] == '|')
        {
            if (!prev || prev->type == TOKEN_OPERATOR)
            {
                printf("syntax error near unexpected token `|'\n");
                return;
            }
        }
        // Check for other invalid operator combinations
        if (curr->type == TOKEN_OPERATOR && prev && prev->type == TOKEN_OPERATOR)
        {
            printf("syntax error near unexpected token `%s'\n", curr->value);
            return;
        }
        prev = curr;
        curr = curr->next;
    }
}


