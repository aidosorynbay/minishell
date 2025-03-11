/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorynbay <@student.42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 18:38:27 by aorynbay          #+#    #+#             */
/*   Updated: 2025/03/11 13:56:38 by aorynbay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	return_tokens(t_token *tokens)
{
	(void)tokens;
	return ;
}

void	signal_handle(int sig)
{
	(void)sig;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

int	main(int ac, char **av, char **envp)
{
	char	*input;
	t_token	*tokens;
	t_env_data data;

	(void)ac;
	(void)av;
	data.env = env_init(envp);
	// (void)envp;
	if (signal(SIGINT, signal_handle) == SIG_ERR)
		perror("signal");
	while (1)
	{
		// if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		// 	perror("signal");
		input = readline("minishell$ ");
		if (!input)
		{
			printf("exit\n");
			break ;
		}
		tokens = tokenize_input(input, &data);
		if (*input)
			add_history(input);
		free(input);
		if (tokens)
			return_tokens(tokens);
	}
}
