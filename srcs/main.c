/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorynbay <@student.42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 18:38:27 by aorynbay          #+#    #+#             */
/*   Updated: 2025/03/11 14:06:55 by aorynbay         ###   ########.fr       */
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
	write(1, "\n", 1);
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
	while (1)
	{
		signal(SIGQUIT, SIG_IGN);
		input = readline("minishell$ ");
		if (!input)
		{
			printf("exit\n");
			break ;
		}
		if (*input)
			add_history(input);
		tokens = tokenize_input(input, &data);
		free(input);
		if (tokens)
			return_tokens(tokens);
	}
}
