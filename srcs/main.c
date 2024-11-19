/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorynbay <@student.42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 18:38:27 by aorynbay          #+#    #+#             */
/*   Updated: 2024/11/19 19:31:20 by aorynbay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **ev)
{
	char	*input;

	(void)ac;
	(void)av;
	(void)ev;

	while (1)
	{
		input = readline("\033[34mminishell$ \033[0m");
		tokenize_input(input);
		if (*input)
			add_history(input);
		// printf("you said: %s\n", input);
		free(input);
	}
	
}