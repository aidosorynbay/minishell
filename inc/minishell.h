#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft.h"

typedef enum e_token_type {
	TOKEN_WORD,
	TOKEN_BUILT_IN,
	TOKEN_OPERATOR,
	TOKEN_ENV_VAR,
	TOKEN_EOF
} t_token_type;

typedef enum S_QUOTE_STATUS {
	Q_NONE,
	Q_SINGLE,
	Q_DOUBLE
} t_quote_status;

typedef struct s_token {
	t_token_type	type;
	char			*value;
	t_quote_status	status;
	struct s_token	*next;
}	t_token;

// tokenization
t_token	*tokenize_input(char *input);
void	tokenization(t_token **tokens, char *input);
void	token_add_back(t_token **lst, t_token *new);
void	create_token(t_token *curr, char *str, int len);
void	print_tokens(t_token *tokens);
char	*two_char_op(char *str, int i);
void	token_clear(t_token *tokens);
void	single_operator(int *start, char *copy, int *i, t_token **tokens);
void	double_operator(int *start, char *copy, int *i, t_token **tokens);


#endif
