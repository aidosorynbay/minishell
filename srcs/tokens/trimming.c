/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trimming.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorynbay <@student.42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 08:39:22 by aorynbay          #+#    #+#             */
/*   Updated: 2025/02/20 08:39:22 by aorynbay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void assign_new_value(t_token *tmp, char *trimmed_value, int *quote_loc)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (tmp->value[i])
    {
        if (i == quote_loc[0] || i == quote_loc[1])
        {
            i++;
            continue;
        }
        trimmed_value[j++] = tmp->value[i++];
    }
    trimmed_value[j] = '\0';
    free(tmp->value);
    tmp->value = trimmed_value;
}

static void  find_last_quote(char *str, int *quote_loc, int len, int i)
{
    while (len >= 0)
    {
        if (str[len] == str[i] && quote_loc[1] == -1)
        {
            quote_loc[1] = len;
            break ;
        }
        len--;
    }
}

static int  *find_quotes(char *str)
{
    int     *quote_loc;
    int     i;
    int     len;

    quote_loc = malloc(2 * sizeof(int));
    if (!quote_loc)
        exit(EXIT_FAILURE);
    i = 0;
    len = ft_strlen(str) - 1;
    quote_loc[0] = -1;
    quote_loc[1] = -1;
    while (str[i])
    {
        if ((str[i] == '\'' || str[i] == '"') && quote_loc[0] == -1)
        {
            quote_loc[0] = i;
            break ;
        }
        i++;
    }
    find_last_quote(str, quote_loc, len, i);
    return (quote_loc);
}

void    trim_quotes(t_token **tokens)
{
    t_token *tmp;
    int     *quote_loc;
    char    *trimmed_value;

    tmp = *tokens;
    while (tmp)
    {   
        quote_loc = find_quotes(tmp->value);
        if (!quote_loc)
        exit(EXIT_FAILURE);
        trimmed_value = malloc(sizeof(char) * (ft_strlen(tmp->value) + 1)); // allocates more memory than needed
        if (!trimmed_value)
        {
            free(quote_loc);
            exit(EXIT_FAILURE);
        }
        assign_new_value(tmp, trimmed_value, quote_loc);
        free(quote_loc);
        tmp = tmp->next;
    }
}
