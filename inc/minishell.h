#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef enum e_token_type {
	TOKEN_WORD,
	TOKEN_BUILT_IN,
	TOKEN_OPERATOR,
	TOKEN_ENV_VAR,
	TOKEN_EOF
} t_token_type;

typedef struct s_token {
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}	t_token;


// tokenization
void	tokenize_input(char *input);


#endif