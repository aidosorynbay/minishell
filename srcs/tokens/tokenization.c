/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorynbay <@student.42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 19:25:00 by aorynbay          #+#    #+#             */
/*   Updated: 2024/12/12 15:52:05 by aorynbay         ###   ########.fr       */
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
	int		i;
	int		start;
	t_token	*curr;

	i = 0;
	start = 0;
	curr = NULL;
	while (copy[i])
	{
		if ((copy[i] == '|' || (copy[i] == '>' && copy[i + 1] != '>')
				|| (copy[i] == '<' && copy[i + 1] != '<')) && i != 0) //need i?
			single_operator(&start, copy, &i, tokens);
		else if ((copy[i] == '>' && copy[i + 1] == '>')
			|| (copy[i] == '<' && copy[i + 1] == '<'))
			double_operator(&start, copy, &i, tokens);
		else
			i++;
	}
	if (start < i)
	{
		curr = malloc(sizeof(t_token));
		create_token(curr, &copy[start], i - start);
		token_add_back(tokens, curr);
	}
}

void	print_tokens(t_token *tokens)
{
	int	i;

	i = 0;
	while (tokens != NULL)
	{
		printf("|%s|\n", tokens->value);
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
	// check_syntax(tokens);
	free(copy);
	print_tokens(tokens);
	return (tokens);
}
