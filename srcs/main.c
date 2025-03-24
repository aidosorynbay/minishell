/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorynbay <@student.42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 18:38:27 by aorynbay          #+#    #+#             */
/*   Updated: 2025/03/24 12:53:27 by aorynbay         ###   ########.fr       */
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

// void	print_env(t_env *list)
// {
// 	while (list)
// 	{
// 		printf("%s=%s\n", list->key, list->value);
// 		list = list->next;
// 	}
// }

int	main(int ac, char **av, char **envp)
{
	char		*input;
	t_token		*tokens;
	t_env_data	data;

	(void)ac;
	(void)av;
	data.env_list = env_init(envp);
	data.last_exit = 0;
	// print_env(data.env_list);
	while (1)
	{
		if (signal(SIGINT, signal_handle) == SIG_ERR)
			perror("signal");
		if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
			perror("signal");
		input = readline("minishell$ ");
		if (!input)
			break ;
		if (*input)
			add_history(input);
		tokens = tokenize_input(input, &data);
		free(input);
		if (tokens)
			return_tokens(tokens);
	}
}
