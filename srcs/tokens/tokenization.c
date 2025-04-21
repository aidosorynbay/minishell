/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorynbay <@student.42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 19:25:00 by aorynbay          #+#    #+#             */
/*   Updated: 2025/04/14 20:41:36 by aorynbay         ###   ########.fr       */
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
	quote_error(quote, tokens);
}

void	tokenize_input(char *input, t_env_data *ev)
{
	t_token	*tokens;
	char	*copy;
	int		i[3];

	i[0] = 0;
	i[1] = 0;
	tokens = NULL;
	i[2] = 0;
	copy = ft_strdup(input);
	tokenization(&tokens, copy, i[0], i[1]);
	free(copy);
	expand_variables(&tokens, ev);
	trim_quotes(&tokens);
	i[2] = check_syntax(&tokens);
	if (i[2] != 0)
	{
		ev->last_exit = i[2];
		if (tokens)
			token_clear(&tokens);
		return ;
	}
	unknown_assign(&tokens);
	assign_token_type(&tokens);
	init_execution(parse_tokens(convert_tokens_to_args(&tokens)), ev);
	return ;
}
