/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohkhan <mohkhan@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 10:56:08 by mohkhan           #+#    #+#             */
/*   Updated: 2025/02/22 10:56:09 by mohkhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_args(char **tokens, int start)
{
	int	count;

	count = 0;
	while (tokens[start] && ft_strcmp(tokens[start], "|") != 0)
	{
		count++;
		start++;
	}
	return (count);
}

t_cmd	*parse_tokens(char **tokens)
{
	t_cmd	*head;
	t_cmd	*current;
	int		i;
	t_cmd	*new_cmd;
	int		arg_count;
	int		j;

	head = NULL;
	current = NULL;
	i = 0;
	while (tokens[i])
	{
		new_cmd = malloc(sizeof(t_cmd));
		if (!new_cmd)
			return (NULL);
		new_cmd->input_fd = STDIN_FILENO;
		new_cmd->output_fd = STDOUT_FILENO;
		new_cmd->cmd_type = TOKEN_UNKNOWN;
		new_cmd->next = NULL;
		arg_count = count_args(tokens, i);
		new_cmd->args = (char **)malloc(sizeof(char *) * (arg_count + 1));
		if (!new_cmd->args)
			return (NULL);
		j = 0;
		while (tokens[i] && ft_strcmp(tokens[i], "|") != 0)
			new_cmd->args[j++] = tokens[i++];
		new_cmd->args[j] = NULL;
		if (new_cmd->args[0] && (ft_strcmp(new_cmd->args[0], "echo") == 0
				|| ft_strcmp(new_cmd->args[0], "cd") == 0
				|| ft_strcmp(new_cmd->args[0], "exit") == 0
				|| ft_strcmp(new_cmd->args[0], "pwd") == 0
				|| ft_strcmp(new_cmd->args[0], "env") == 0
				|| ft_strcmp(new_cmd->args[0], "export") == 0))
			new_cmd->cmd_type = TOKEN_BUILTIN;
		// fprintf(stderr, "Command: %d\n", new_cmd->cmd_type);
		if (!head)
			head = new_cmd;
		else
			current->next = new_cmd;
		current = new_cmd;
		if (tokens[i] && ft_strcmp(tokens[i], "|") == 0)
			i++;
	}
	return (head);
}
