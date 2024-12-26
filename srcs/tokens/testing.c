


// # include <stdio.h>
// # include <stdlib.h>
// # include <unistd.h>
// # include <sys/types.h>
// # include <sys/wait.h>
// # include <string.h>
// # include <readline/readline.h>
// # include <readline/history.h>
// // # include "libft.h"
// //2 ^ n processes will be created for n fork() callsm

// int main(int argc, char *argv[])
// {
//     int id = fork();
//     int n;
//     if (id == 0)
//     {
//         n = 1;
//         // fork();
//         // printf("Hello, World! Forked from child process: %d\n", id);
//     }
//     else
//         n = 6;
//         // printf("Hello, World!\n");
//     if (id != 0)
//         wait(NULL);
//     int i;
//     for (i = n; i < n + 5; i++)
//     {
//         printf("%d ", i);
//         fflush(stdout);
//     }
//     if (id != 0)
//         printf("\n");
//     // if (id == 0)
//         // printf("Hello, World! from child process: %d\n", id);
//     // else
//         // printf("Hello, World! from parent process: %d\n", id);
//     return (0);
// }


// additional stuff
		// if (strcmp(tmp->value, ">>>") == 0)
		// {
		// 	if (tmp->next == NULL)
		// 	{
		// 		perror("exit: 258 syntax error near unexpected token `>'");
		// 		return ;
		// 	}
		// 	if (strcmp(tmp-> next -> value, "<<") == 0 || strcmp(tmp-> next -> value, ">") == 0 || strcmp(tmp-> next -> value, "<") == 0 
		// 		|| strcmp(tmp-> next -> value, ">>") == 0 || strcmp(tmp-> next -> value, "|") == 0 || strcmp(tmp-> next -> value, ";") == 0)
		// 	{
		// 		perror("exit: 258 syntax error near unexpected token `>>'");
		// 		return ;
		// 	}
		// 	else
		// 	{
		// 		perror("exit: 258 syntax error near unexpected token `;'");
		// 		return ;
		// 	}
		// }
		// if (strcmp(tmp->value, "<<<") == 0)
		// {
		// 	if (tmp->next == NULL)
		// 	{
		// 		perror("exit: 258 syntax error near unexpected token `>'");
		// 		return ;
		// 	}
		// 	if (strcmp(tmp-> next -> value, "<<") == 0 || strcmp(tmp-> next -> value, ">") == 0 || strcmp(tmp-> next -> value, "<") == 0 
		// 		|| strcmp(tmp-> next -> value, ">>") == 0 || strcmp(tmp-> next -> value, "|") == 0 || strcmp(tmp-> next -> value, ";") == 0)
		// 	{
		// 		perror("exit: 258 syntax error near unexpected token `>>'");
		// 		return ;
		// 	}
		// 	else
		// 	{
		// 		perror("exit: 258 syntax error near unexpected token `;'");
		// 		return ;
		// 	}
		// }

        		// if (strcmp(tmp->value, "||") == 0)
		// {
		// 	if (tmp->next == NULL)
		// 	{
		// 		perror("exit: 258 syntax error near unexpected token `|'");
		// 		return ;
		// 	}
		// 	if (strcmp(tmp-> next -> value, "<<") == 0 || strcmp(tmp-> next -> value, ">") == 0 || strcmp(tmp-> next -> value, "<") == 0 
		// 		|| strcmp(tmp-> next -> value, ">>") == 0 || strcmp(tmp-> next -> value, "|") == 0 || strcmp(tmp-> next -> value, ";") == 0)
		// 	{
		// 		perror("exit: 258 syntax error near unexpected token `|'");
		// 		return ;
		// 	}
		// 	else
		// 	{
		// 		perror("exit: 258 syntax error near unexpected token `;'");
		// 		return ;
		// 	}
		// }
		// printf("%s\n", tmp->value);


        // 		printf("%s\n", tmp->value);
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
		// if (strcmp(tmp->value, ";;") == 0)
		// {
		// 	perror("exit: 258 syntax error near unexpected token `;'");
		// 	return ;
		// }