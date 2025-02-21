#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft.h"
# include <string.h>
# include <fcntl.h>

# include <signal.h>

typedef enum e_token_type {
	TOKEN_CMD, // commands
	TOKEN_BUILTIN, // echo, cd, pwd, export etc.
	TOKEN_ARG, // arguments
	TOKEN_PIPE, // |
	TOKEN_REDIRECT_IN, // <
	TOKEN_REDIRECT_OUT, // >
	TOKEN_REDIRECT_APPEND, // >>
	TOKEN_HEREDOC, // <<
	TOKEN_FILE,
	TOKEN_BUILTIN_FLAG, // -n
	TOKEN_EOF, // for heredoc
	TOKEN_UNKNOWN
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

typedef struct s_cmd {
	char			*cmd;
	char			**args;
	char			**args_for_cmd;
	int				argc;
	struct s_cmd	*next;
	int				input_fd;
	int				output_fd;
	char *outfile;
	char *inputfile;
	int				append_fd;
	// int				heredoc;
	t_token_type	cmd_type;
}	t_cmd;

// tokenization
t_token	*tokenize_input(char *input);
void	tokenization(t_token **tokens, char *input, int i, int start);
void	create_token(t_token *curr, char *str, int len);
void	print_tokens(t_token *tokens);
// token_utils
void	token_add_back(t_token **lst, t_token *new);
char	*two_char_op(char *str, int i);
void	token_clear(t_token **tokens);
void	single_operator(int *start, char *copy, int *i, t_token **tokens);
void	double_operator(int *start, char *copy, int *i, t_token **tokens);
// more_utils
void 	quote_error(t_quote_status quote);
void	assign_quote(char *copy, int *i, t_quote_status *quote);
void	create_and_add_token(t_token **tokens, char *copy, int start, int end);

// syntax_check
void 	check_syntax(t_token **tokens);
// syntax_check_utils
int		checker(t_token *tmp, t_token **tokens);
int		check_here_doc(t_token *tmp, t_token **tokens);

// assign type
void	assign_token_type(t_token **tokens);
void	unknown_assign(t_token **tokens);

//converter
char **convert_tokens_to_args(t_token *tokens);


//utils
void    clear_screen(void);

//execution
t_cmd *parse_tokens(char **av);

//builtins
void init_execution(t_cmd *cmd_list);
int ft_echo(char **total_arg);
int ft_exit(char **total_arg);
int ft_cd(char **total_arg);
void ft_pwd();


#endif
