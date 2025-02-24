/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorynbay <@student.42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 18:38:27 by aorynbay          #+#    #+#             */
/*   Updated: 2025/02/20 10:13:39 by aorynbay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	return_tokens(t_token *tokens)
{
	(void)tokens;
	return ;
}
		// if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		// 	perror("signal");
		// if (signal(SIGINT, SIG_IGN) == SIG_ERR)
		// 	perror("signal");

int	main(int ac, char **av, char **envp)
{
	char	*input;
	t_token	*tokens;
	t_env_data data;

	(void)ac;
	(void)av;
    data.envp = envp;
	data.env = env_init(envp);
	while (1)
	{
		input = readline("minishell$ ");
		if (!input)
			break ;
		tokens = tokenize_input(input, &data);
		if (*input)
			add_history(input);
		free(input);
		if (tokens)
			return_tokens(tokens);
	}
}
