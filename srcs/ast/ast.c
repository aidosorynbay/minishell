#include "minishell.h"

void    build_ast(t_token **tokens)
{
    t_token *token;
    t_ast   *ast;

    token = *tokens;
    ast = (t_ast *)malloc(sizeof(t_ast));
    ast->type = token->type;
    ast->value = token->value;
    ast->left = NULL;
    ast->right = NULL;
    *tokens = token->next;
    else if (ast->type == PIPE)
    {
        build_ast(&ast->left);
        build_ast(&ast->right);
    }
    else if (ast->type == REDIRECT)
    {
        build_ast(&ast->left);
        build_ast(&ast->right);
    }
    else if (ast->type == COMMAND)
    {
        build_ast(&ast->left);
        build_ast(&ast->right);
    }
    else if (ast->type == ARGUMENT)
    {
        build_ast(&ast->left);
        build_ast(&ast->right);
    }
    else if (ast->type == ENVIRONMENT)
    {
        build_ast(&ast->left);
        build_ast(&ast->right);
    }
    else if (ast->type == VARIABLE)
    {
        build_ast(&ast->left);
        build_ast(&ast->right);
    }
    else if (ast->type == VALUE)
    {
        build_ast(&ast->left);
        build_ast(&ast->right);
    }
    else if (ast->type == QUOTE)
    {
        build_ast(&ast->left);
        build_ast(&ast->right);
    }
    else if (ast->type == DQUOTE)
    {
        build_ast(&ast->left);
        build_ast(&ast->right);
    }
    else if (ast->type == BQUOTE)
    {
        build_ast(&ast->left);
        build_ast(&ast->right);
    }
    else if (ast->type == PARENTHESIS)
    {
        build_ast(&ast->left);
        build_ast(&ast->right);
    }
    else if (ast->type == BRACES)
    {
        build_ast(&ast->left);
        build_ast(&ast->right);
    }
    else if (ast->type == BRACKETS)
    {
        build_ast(&ast->left);
        build_ast(&ast->right);
    }
}
