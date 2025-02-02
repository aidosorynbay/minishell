#include "minishell.h"

// void    build_ast(t_token **tokens)
// {
//     t_token *token;
//     t_ast   *ast;

//     token = *tokens;
//     ast = (t_ast *)malloc(sizeof(t_ast));
//     ast->type = token->type;
//     ast->value = token->value;
//     // ast->left = NULL;
//     // ast->right = NULL;
//     *tokens = token->next;
//     // if (ast->type == TOKEN_PIPE)
//     // {
//     //     build_ast(&ast->left);
//     //     build_ast(&ast->right);
//     // }
// }
