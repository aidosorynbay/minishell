/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorynbay <@student.42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 19:25:00 by aorynbay          #+#    #+#             */
/*   Updated: 2025/01/29 18:06:04 by aorynbay         ###   ########.fr       */
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
		printf("value: {%s}\n", tokens->value);
		if (tokens->type == 0)
			printf("type: |TOKEN_CMD|\n");
		else if (tokens->type == 1)
			printf("type: |TOKEN_BUILTIN|\n");
		else if (tokens->type == 2)
			printf("type: |TOKEN_ARG|\n");
		else if (tokens->type == 3)
			printf("type: |TOKEN_PIPE|\n");
		else if (tokens->type == 4)
			printf("type: |TOKEN_REDIRECT_IN|\n");
		else if (tokens->type == 5)
			printf("type: |TOKEN_REDIRECT_OUT|\n");
		else if (tokens->type == 6)
			printf("type: |TOKEN_REDIRECT_APPEND|\n");
		else if (tokens->type == 7)
			printf("type: |TOKEN_HEREDOC|\n");
		else if (tokens->type == 8)
			printf("type: |TOKEN_FILE|\n");
		else if (tokens->type == 10)
			printf("UNKNOWN TYPE\n");
		else if (tokens->type == 9)
			printf("type: |TOKEN_BUILTIN_FLAG|\n");
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
	check_syntax(&tokens);
	assign_token_type(&tokens);
	print_tokens(tokens);
	free(copy);
	if (tokens)
		token_clear(&tokens);
	return (tokens);
}
