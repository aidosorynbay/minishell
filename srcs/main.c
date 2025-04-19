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

void	free_tokens(char **tokens)
{
    int i = 0;

    if (!tokens)
        return;

    while (tokens[i])
    {
        free(tokens[i]);
        i++;
    }
    free(tokens);
}

void free_cmd_list(t_cmd *cmd_list)
{
    t_cmd *temp;

    while (cmd_list)
    {
        temp = cmd_list;
        cmd_list = cmd_list->next;

        // Free inputfile and outfile
        if (temp->inputfile)
            free(temp->inputfile);
        if (temp->outfile)
            free(temp->outfile);
        
        // Free heredoc_path if it exists
        if (temp->heredoc_path)
            free(temp->heredoc_path);

        // Free args_for_cmd
        if (temp->args_for_cmd)
        {
            int i = 0;
            while (temp->args_for_cmd[i])
            {
                free(temp->args_for_cmd[i]);
                i++;
            }
            free(temp->args_for_cmd);
        }

        // Free args
        if (temp->args)
        {
            int i = 0;
            while (temp->args[i])
            {
                free(temp->args[i]);
                i++;
            }
            free(temp->args);
        }

        // Free the command node itself
        free(temp);
    }
}

void free_args_for_cmd(char **args)
{
    int i = 0;

    if (!args)
        return;

    while (args[i])
    {
        free(args[i]);
        i++;
    }
    free(args);
}

void	free_env_list(t_env *env_list)
{
	t_env	*temp;

	while (env_list)
	{
		temp = env_list;
		env_list = env_list->next;
		free(temp->key);
		free(temp->value);
		free(temp);
	}
}

void	free_env_data(t_env_data *env_data)
{
    if (!env_data)
        return;
    free_env_list(env_data->env_list);
    free_env_list(env_data->env_export_list);
    free(env_data);
}


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
		if (tokens != NULL)
			return_tokens(tokens);
	}
    free_env_data(data);
	exit(g_exit_code);
}
