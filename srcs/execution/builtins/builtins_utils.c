// #include "minishell.h"

// int    check_file_existence(t_token **tokens)
// {
//     t_token *tmp = *tokens;

//     while (tmp->value)
//     {
//         if (tmp->type == TOKEN_REDIRECT_IN)
//         {
//             if (access(tmp->next->value, F_OK) == -1)
//             {
//                 fprintf(stderr, "minishell: %s: No such file or directory\n", tmp->next->value);
//                 return (-1);
//             }
//         }
//         tmp = tmp->next;
//     }
//     return (0);
// }