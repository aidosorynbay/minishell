/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorynbay <@student.42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 18:38:27 by aorynbay          #+#    #+#             */
/*   Updated: 2025/04/18 17:08:14 by aorynbay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_code = 0;

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
	g_exit_code = 1;
}

int main(int ac, char **av, char **envp)
{
	char        *input;
	t_token     *tokens;
	t_env_data  *data;

	(void)ac;
	(void)av;
	data = env_init(envp);
	if (data == NULL)
	{
		perror("env_init failed");
		return (EXIT_FAILURE);
	}
	while (1)
	{
		if (signal(SIGINT, signal_handle) == SIG_ERR)
			perror("signal");
		if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
			perror("signal");
		input = readline("minishell$ ");
		if (input == NULL)
			break;
		if (*input != '\0')
			add_history(input);
		tokens = tokenize_input(input, data);
		free(input);
        input = NULL;
		if (tokens != NULL)
			return_tokens(tokens);
	}
    free_env_data(data);
	exit(g_exit_code);
}
