#include "minishell.h"

// char **convert_tokens_to_args(t_token **tokens)
// {
//     int count;
//     int i;
//     t_token **tmp;

//     tmp = tokens;
//     count = 0;
//     i = 0;

//     while (tmp && (*tmp)->type != TOKEN_PIPE)
//     {
//         count++;
//         (*tmp) = (*tmp)->next;
//     }

//     char **args = (char **)malloc((count + 1) * sizeof(char *));
//     if (!args)
//         return NULL;

//     (*tmp) = tokens;
//     while(i < count)
//     {
//         args[i++] = strdup((*tmp)->value);
//         (*tmp) = (*tmp)->next;
//     }
//     args[count] = NULL;
//     return args;
// }
