/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorynbay <@student.42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 19:25:00 by aorynbay          #+#    #+#             */
/*   Updated: 2025/01/06 10:43:22 by aorynbay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_token(t_token *curr, char *str, int len)
{
	curr->value = ft_substr(str, 0, len);
	curr->next = NULL;
}

void	tokenization(t_token **tokens, char *copy)
{
	int				i;
	int				start;
	t_quote_status	quote;

	i = 0;
	start = 0;
	quote = Q_NONE;
	while (copy[i])
	{
		assign_quote(copy, &i, &quote);
		if (copy[i] == ' ' && quote == Q_NONE)
		{
			if (start < i)
				create_and_add_token(tokens, copy, start, i);
			start = i + 1;
		}
		operator_delimiter(&start, copy, &i, tokens);
	}
	if (start < i)
		create_and_add_token(tokens, copy, start, i);
	quote_error(quote);
}

void	print_tokens(t_token *tokens)
{
	int	i;

	i = 0;
	while (tokens != NULL)
	{
		printf("{%s}\n", tokens->value);
		tokens = tokens->next;
		i++;
	}
	printf("%d\n", i);
}

t_token	*tokenize_input(char *input)
{
	t_token	*tokens;
	char	*copy;

	tokens = NULL;
	copy = ft_strdup(input);
	tokenization(&tokens, copy);
	free(copy);
	print_tokens(tokens);
	return (tokens);
}
