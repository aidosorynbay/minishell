/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorynbay <@student.42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 12:53:54 by aorynbay          #+#    #+#             */
/*   Updated: 2025/01/07 17:37:49 by aorynbay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	token_add_back(t_token **lst, t_token *new)
{
	t_token	*curr;
	t_token	*temp;

	if (new == NULL)
		return ;
	if (lst == NULL || *lst == NULL)
		*lst = new;
	else
	{
		curr = *lst;
		temp = curr;
		while (curr->next != NULL)
		{
			curr = curr->next;
		}
		curr->next = new;
		*lst = temp;
	}
}

char	*two_char_op(char *str, int i)
{
	char	*res;

	res = malloc(sizeof(char) * 3);
	if (!res)
		return (NULL);
	res[0] = str[i];
	res[1] = str[i + 1];
	res[2] = '\0';
	return (res);
}

void	token_clear(t_token **tokens)
{
	t_token	*temp;

	while (*tokens != NULL)
	{
		temp = (*tokens)->next;
		free((*tokens)->value);
		(*tokens)->value = NULL;
		free(*tokens);
		*tokens = temp;
	}
	*tokens = NULL;
}

void	single_operator(int *start, char *copy, int *i, t_token **tokens)
{
	t_token	*curr;

	curr = malloc(sizeof(t_token));
	create_token(curr, &copy[*start], *i - *start);
	if (curr->value && curr->value[0] != '\0')
		token_add_back(tokens, curr);
	else
	{
		free(curr->value);
		free(curr);
	}
	curr = malloc(sizeof(t_token));
	curr->value = ft_substr(&copy[*i], 0, 1);
	curr->next = NULL;
	if (curr->value && curr->value[0] != '\0')
		token_add_back(tokens, curr);
	else
	{
		free(curr->value);
		free(curr);
	}
	(*i)++;
	*start = *i;
}

void	double_operator(int *start, char *copy, int *i, t_token **tokens)
{
	t_token	*curr;

	curr = malloc(sizeof(t_token));
	create_token(curr, &copy[*start], *i - *start);
	if (curr->value && curr->value[0] != '\0')
		token_add_back(tokens, curr);
	else
	{
		free(curr->value);
		free(curr);
	}
	curr = malloc(sizeof(t_token));
	curr->value = two_char_op(copy, *i);
	curr->next = NULL;
	if (curr->value && curr->value[0] != '\0')
		token_add_back(tokens, curr);
	else
	{
		free(curr->value);
		free(curr);
	}
	*i += 2;
	*start = *i;
}
