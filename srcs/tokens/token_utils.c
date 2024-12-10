/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorynbay <@student.42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 12:53:54 by aorynbay          #+#    #+#             */
/*   Updated: 2024/12/10 18:35:40 by aorynbay         ###   ########.fr       */
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

void	token_clear(t_token *tokens)
{
	t_token	*temp;

	while (tokens != NULL)
	{
		temp = tokens;
		tokens = tokens->next;
		free(temp->value);
		free(temp);
		printf("Freed a token\n");
	}
}

void	single_operator(t_token *curr, int *start, char *copy, int *i, t_token **tokens)
{
	curr = malloc(sizeof(t_token));
	create_token(curr, &copy[*start], *i - *start);
	token_add_back(tokens, curr);
	curr = malloc(sizeof(t_token));
	curr->value = ft_substr(&copy[*i], 0, 1);
	curr->next = NULL;
	token_add_back(tokens, curr);
	(*i)++;
	*start = *i;
}

void	double_operator(t_token *curr, int *start, char *copy, int *i, t_token **tokens)
{
	curr = malloc(sizeof(t_token));
	create_token(curr, &copy[*start], *i - *start);
	token_add_back(tokens, curr);
	curr = malloc(sizeof(t_token));
	curr->value = two_char_op(copy, *i);
	curr->next = NULL;
	token_add_back(tokens, curr);
	*i += 2;
	*start = *i;
}
