/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohkhan <mohkhan@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 18:38:27 by aorynbay          #+#    #+#             */
/*   Updated: 2025/04/21 19:27:24 by mohkhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		g_exit_code = 0;

void	signal_handle(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_exit_code = 1;
}

static	void	check_input(char *input)
{
	if (input == NULL)
	{
		write(1, "exit\n", 5);
		exit(0);
	}
	if (*input == '\0')
	{
		free(input);
		return ;
	}
}

void	signal_handle_heredoc(void)
{
	if (signal(SIGINT, signal_handle) == SIG_ERR)
		perror("signal");
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		perror("signal");
}

int	main(int ac, char **av, char **envp)
{
	char		*input;
	t_env_data	*data;

	(void)ac;
	(void)av;
	data = env_init(envp);
	if (data == NULL)
		return (perror("env_init failed"), (1));
	while (1)
	{
		signal_handle_heredoc();
		input = readline("minishell$ ");
		check_input(input);
		if (*input != '\0')
			add_history(input);
		tokenize_input(input, data);
		input = NULL;
	}
	free_env_data(data);
	exit(g_exit_code);
}
