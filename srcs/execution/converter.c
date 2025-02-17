#include "minishell.h"

char **convert_tokens_to_args(t_token *tokens)
{
    int count;
    int i;
    t_token *tmp;

    tmp = tokens;
    count = 0;
    i = 0;
    while (tmp)
    {
        count++;
        tmp = tmp->next;
    }
    char **args = (char **)malloc((count + 1) * sizeof(char *));
    if (!args)
        return NULL;
    tmp = tokens;
    while(i < count)
    {
        // printf("values are: %s\n", tmp->value);
        args[i] = strdup(tmp->value);
        i++;
        tmp = tmp->next;
    }
    args[count] = NULL;
    return args;
}
