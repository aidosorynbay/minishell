/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorynbay <@student.42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 18:38:27 by aorynbay          #+#    #+#             */
/*   Updated: 2024/12/10 18:26:32 by aorynbay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **ev)
{
	char	*input;
	t_token	*tokens;

	(void)ac;
	(void)av;
	(void)ev;
	while (1)
	{
		input = readline("\033[34mminishell$ \033[0m");
		tokens = tokenize_input(input);
		check_syntax(tokens);
		if (*input)
			add_history(input);
		free(input);
		token_clear(tokens);
	}
}
