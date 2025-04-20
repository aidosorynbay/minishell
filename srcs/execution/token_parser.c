/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aorynbay <@student.42abudhabi.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 10:56:08 by mohkhan           #+#    #+#             */
/*   Updated: 2025/04/18 16:19:33 by aorynbay         ###   ########.fr       */
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
void	initialize_cmd(t_cmd *new_cmd)
{
	new_cmd->input_fd = STDIN_FILENO;
	new_cmd->output_fd = STDOUT_FILENO;
	new_cmd->cmd_type = TOKEN_UNKNOWN;
	new_cmd->envp = NULL;
	new_cmd->next = NULL;
	new_cmd->args = NULL;
	new_cmd->args_for_cmd = NULL;
	new_cmd->inputfile = NULL;
	new_cmd->outfile = NULL;
	new_cmd->append_fd = 0;
	new_cmd->has_heredoc = 0;
	new_cmd->heredoc_path = NULL;
}

void assign_new_cmd_type(t_cmd *new_cmd)
{
	if (new_cmd->args[0] && (ft_strcmp(new_cmd->args[0], "echo") == 0
		|| ft_strcmp(new_cmd->args[0], "cd") == 0
		|| ft_strcmp(new_cmd->args[0], "exit") == 0
		|| ft_strcmp(new_cmd->args[0], "unset") == 0
		|| ft_strcmp(new_cmd->args[0], "pwd") == 0
		|| ft_strcmp(new_cmd->args[0], "env") == 0
		|| ft_strcmp(new_cmd->args[0], "export") == 0))
		new_cmd->cmd_type = TOKEN_BUILTIN;
	else
		new_cmd->cmd_type = TOKEN_CMD;
}
t_cmd	*	parse_tokens(char **tokens)
{
	t_cmd	*head;
	t_cmd	*current;
	int		i[3]; //i[0] is i && i[1] is j && i[2] is args count
	t_cmd	*new_cmd;

	head = NULL;
	current = NULL;
	i[0] = 0;
	while (tokens[i[0]])
	{
		new_cmd = malloc(sizeof(t_cmd));
		if (!new_cmd)
			return(free_tokens(tokens), NULL);
		i[2] = count_args(tokens, i[0]);
		initialize_cmd(new_cmd);
		new_cmd->args = (char **)malloc(sizeof(char *) * (i[2] + 1));
		if (!new_cmd->args)
			return(free_tokens(tokens), NULL);
		i[1] = 0;
		while (tokens[i[0]] && ft_strcmp(tokens[i[0]], "|") != 0)
			new_cmd->args[i[1]++] = ft_strdup(tokens[i[0]++]);
		new_cmd->args[i[1]] = NULL;
		assign_new_cmd_type(new_cmd);
		if (!head)
			head = new_cmd;
		else
			current->next = new_cmd;
		current = new_cmd;
		if (tokens[i[0]] && ft_strcmp(tokens[i[0]], "|") == 0)
			i[0]++;
	}
	free_tokens(tokens);
	return (head);
}
