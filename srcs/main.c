/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorynbay <@student.42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 18:38:27 by aorynbay          #+#    #+#             */
/*   Updated: 2025/01/07 17:41:29 by aorynbay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	return_tokens(t_token *tokens)
{
	(void)tokens;
	return ;
}

int	main(int ac, char **av, char **ev)
{
	char	*input;
	t_token	*tokens;

	(void)ac;
	(void)av;
	(void)ev;
	while (1)
	{
		input = readline("minishell$ ");
		tokens = tokenize_input(input);
		if (*input)
			add_history(input);
		free(input);
		if (tokens)
			return_tokens(tokens);
	}
}
