// #include "minishell.h"

// t_ast *create_simple_command(char *command) {
//     t_ast *node = malloc(sizeof(t_ast));
//     node->value = ft_strdup(command);
//     node->left = NULL;
//     node->right = NULL;
//     return node;
// }

// t_token *find_main_operator(t_token *tokens) {
//     t_token *current = tokens;

//     // Iterate through the token list
//     while (current != NULL) {
//         if (ft_strcmp(current->value, "|") == 0 ||  // Pipe
//             ft_strcmp(current->value, ">") == 0 || // Redirect
//             ft_strcmp(current->value, "<") == 0) { // Input redirect
//             return current; // Return the first operator found
//         current = current->next;
//     }
//     return NULL; // No operator found
// }

// // t_token *get_left_tokens(t_token *tokens, t_token *main_op) {
// //     t_token *left = NULL;
// //     t_token *current = tokens;

// //     while (current != NULL && current != main_op) {
// //         t_token *new_token = malloc(sizeof(t_token));
// //         new_token->value = ft_strdup(current->value);
// //         new_token->next = NULL;
// //         token_add_back(&left, new_token); // Add to the left list
// //         current = current->next;
// //     }
// //     return left; // Return the left tokens
// // }

// // t_token *get_right_tokens(t_token *main_op) {
// //     t_token *right = NULL;
// //     t_token *current = main_op->next; // Start after the operator

// //     while (current != NULL)
// //     {
// //         t_token *new_token = malloc(sizeof(t_token));
// //         new_token->value = ft_strdup(current->value);
// //         new_token->next = NULL;
// //         token_add_back(&right, new_token); // Add to the right list
// //         current = current->next;
// //     }
// //     return right; // Return the right tokens
// // }

// // t_ast *build_ast(t_token *tokens) {
// //     if (tokens == NULL)
// //         return NULL;

// //     // Find the main operator (e.g., `|`, `>`)
// //     t_token *main_op = find_main_operator(tokens);

// //     if (main_op) {
// //         t_ast *node = malloc(sizeof(t_ast));
// //         node->value = ft_strdup(main_op->value); // Store the operator

// //         // Split tokens into left and right parts
// //         t_token *left_tokens = get_left_tokens(tokens, main_op);
// //         t_token *right_tokens = get_right_tokens(main_op);

// //         // Recursively build left and right subtrees
// //         node->left = build_ast(left_tokens);
// //         node->right = build_ast(right_tokens);

// //         return node;
// //     }

// //     // If no operator, it's a simple command
// //     return create_simple_command(tokens->value);
// // }

// // void print_ast(t_ast *node, int depth) {
// //     if (node == NULL)
// //         return;

// //     for (int i = 0; i < depth; i++)
// //         printf("  "); // Indentation
// //     printf("%s\n", node->value);

// //     print_ast(node->left, depth + 1);
// //     print_ast(node->right, depth + 1);
// // }
