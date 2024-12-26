#include "minishell.h"

#include <stdio.h>
#include <string.h>
#include "minishell.h"

void check_syntax(t_token *tokens)
{
	t_token *tmp;

	tmp = tokens;
	while (tmp)
	{
		// if (strcmp(tmp->value, ";") == 0)
		// {
		// 	if (tmp->next == NULL || tmp->prev == NULL)
		// 	{
		// 		perror("exit: 258 syntax error near unexpected token `;'");
		// 		return ;
		// 	}
		// 	if (strcmp(tmp-> next -> value, "<<") == 0 || strcmp(tmp-> next -> value, ">") == 0 || strcmp(tmp-> next -> value, "<") == 0 
		// 		|| strcmp(tmp-> next -> value, ">>") == 0 || strcmp(tmp-> next -> value, "|") == 0 || strcmp(tmp-> next -> value, ";") == 0)
		// 	{
		// 		perror("exit: 258 syntax error near unexpected token `;'");
		// 		return ;
		// 	}

		// }
		// // printf("%s\n", tmp->value);
		// if (strcmp(tmp->value, ";;") == 0)
		// {
		// 	perror("exit: 258 syntax error near unexpected token `;'");
		// 	return ;
		// }
		printf("%s\n", tmp->value);
		if (strcmp(tmp->value, "|") == 0)
		{
			if (tmp->next == NULL)
			{
				perror("exit: 258 syntax error near unexpected token `|'");
				return ;
			}
			if (strcmp(tmp-> next -> value, "<<") == 0 || strcmp(tmp-> next -> value, ">") == 0 || strcmp(tmp-> next -> value, "<") == 0 
				|| strcmp(tmp-> next -> value, ">>") == 0 || strcmp(tmp-> next -> value, "|") == 0 || strcmp(tmp-> next -> value, ";") == 0)
			{
				perror("exit: 258 syntax error near unexpected token `|'");
				return ;
			}
		}
		if (strcmp(tmp->value, ">>") == 0)
		{
			if (tmp->next == NULL)
			{
				perror("exit: 258 syntax error near unexpected token `>'");
				return ;
			}
			if (strcmp(tmp-> next -> value, "<<") == 0 || strcmp(tmp-> next -> value, ">") == 0 || strcmp(tmp-> next -> value, "<") == 0 
				|| strcmp(tmp-> next -> value, ">>") == 0 || strcmp(tmp-> next -> value, "|") == 0 || strcmp(tmp-> next -> value, ";") == 0)
			{
				perror("exit: 258 syntax error near unexpected token `>>'");
				return ;
			}
		}
		if (strcmp(tmp->value, "<<") == 0)
		{
			if (tmp->next == NULL)
			{
				perror("exit: 258 exit: 258 syntax error near unexpected token `<'");
				return ;
			}
			printf("%s", tmp->next->value);
			perror("hello");
			if (strcmp(tmp-> next -> value, "<<") == 0 || strcmp(tmp-> next -> value, ">") == 0 || strcmp(tmp-> next -> value, "<") == 0 
				|| strcmp(tmp-> next -> value, ">>") == 0 || strcmp(tmp-> next -> value, "|") == 0 || strcmp(tmp-> next -> value, ";") == 0)
			{
				perror("exit: 258 syntax error near unexpected token `<<'");
				return ;
			}
		}
		tmp = tmp->next;
	}
	return ;

}


