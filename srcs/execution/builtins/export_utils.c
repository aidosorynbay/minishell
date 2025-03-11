
#include "minishell.h"

// int is_valid_env_key(char *key)
// {
//     if (!key || !*key)
//         return 1; // Empty key is invalid

//     // First character must be a letter or underscore
//     if (!(ft_isalpha(*key) || *key == '_'))
//         return 1;

//     while (*++key)
//     {
//         if (!(ft_isalnum(*key) || *key == '_'))
//             return 1;
//     }
//     return 0;
// }