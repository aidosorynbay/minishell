/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorynbay <@student.42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 19:25:00 by aorynbay          #+#    #+#             */
/*   Updated: 2024/12/25 17:16:41 by aorynbay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_token(t_token *curr, char *str, int len)
{
	curr->value = ft_substr(str, 0, len);
	curr->next = NULL;
}

void	tokenization(t_token **tokens, char *copy, int i, int start)
{
	t_quote_status	quote;

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
		if ((copy[i] == '|' || (copy[i] == '>' && copy[i + 1] != '>')
				|| (copy[i] == '<' && copy[i + 1] != '<')) && quote == Q_NONE)
			single_operator(&start, copy, &i, tokens);
		else if (((copy[i] == '>' && copy[i + 1] == '>')
				|| (copy[i] == '<' && copy[i + 1] == '<')) && quote == Q_NONE)
			double_operator(&start, copy, &i, tokens);
		else
			i++;
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
	int		i;
	int		start;

	i = 0;
	start = 0;
	tokens = NULL;
	copy = ft_strdup(input);
	tokenization(&tokens, copy, i, start);
	check_syntax(tokens);
	free(copy);
	print_tokens(tokens);
	return (tokens);
}
