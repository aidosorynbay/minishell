/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohkhan <mohkhan@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 19:38:33 by mohkhan           #+#    #+#             */
/*   Updated: 2025/04/21 19:38:33 by mohkhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <errno.h> // can we have this????
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

extern int	g_exit_code;

typedef enum e_token_type
{
	TOKEN_CMD,	// commands
	TOKEN_BUILTIN,	// echo, cd, pwd, export etc.
	TOKEN_ARG,	// arguments
	TOKEN_PIPE,	// |
	TOKEN_REDIRECT_IN,	// <
	TOKEN_REDIRECT_OUT,	// >
	TOKEN_REDIRECT_APPEND,	// >>
	TOKEN_HEREDOC,	// <<
	TOKEN_FILE,
	TOKEN_BUILTIN_FLAG,	// -n
	TOKEN_EOF,	// for heredoc
	TOKEN_UNKNOWN
}	t_token_type;

typedef enum S_QUOTE_STATUS
{
	Q_NONE,
	Q_SINGLE,
	Q_DOUBLE
}	t_quote_status;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	t_quote_status	status;
	struct s_token	*next;
}	t_token;

typedef struct s_cmd
{
	char			**args;
	char			**args_for_cmd;
	int				count_cmd;
	int				input_fd;
	int				output_fd;
	char			*outfile;
	char			*inputfile;
	int				append_fd;
	int				has_heredoc;
	char			*heredoc_path;
	char			**envp;
	t_token_type	cmd_type;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_env
{
	char			*key;	// Variable name (e.g., "PATH")
	char			*value;	// Variable value (e.g., "/usr/bin")
	int				has_value;
	struct s_env	*next;
}	t_env;

typedef struct s_env_data
{
	t_env	*env_list;	// Env linked list
	t_env	*env_export_list;	// for export
	int		last_exit;	// Store last exit status ($?)
}	t_env_data;

// tokenization
t_token		*tokenize_input(char *input, t_env_data *ev);
void		tokenization(t_token **tokens, char *input, int i, int start);
void		create_token(t_token *curr, char *str, int len);

// token_utils
void		token_add_back(t_token **lst, t_token *new);
char		*two_char_op(char *str, int i);
void		token_clear(t_token **tokens);
void		single_operator(int *start, char *copy, int *i, t_token **tokens);
void		double_operator(int *start, char *copy, int *i, t_token **tokens);

// more_utils
void		quote_error(t_quote_status quote, t_token **tokens);
void		assign_quote(char *copy, int *i, t_quote_status *quote);
void		create_and_add_token(t_token **tokens, char *copy,
				int start, int end);

// syntax_check
int			check_syntax(t_token **tokens);

// syntax_check_utils
int			checker(t_token *tmp, t_token **tokens);
int			check_here_doc(t_token *tmp, t_token **tokens);
int			check_lesser(t_token *tmp, t_token **tokens);
int			check_redirection(t_token *tmp, t_token **tokens);
int			error_syntaxcheck(t_token **tokens);

// assign type
void		assign_token_type(t_token **tokens);
void		assign_builtin_type(t_token *tmp);
void		assign_op_type(t_token *tmp);
void		unknown_assign(t_token **tokens);
void		assign_op_eof(t_token *tmp, int *expect_eof);
void		handle_op(t_token *tmp, int *expect_file, int *expect_eof,
				int *expect_command);
void		handle_comman_file(t_token *tmp, t_token **tokens, int *expect_file,
				int *expect_command);

// trimming
void		trim_quotes(t_token **tokens);

// converter
char		**convert_tokens_to_args(t_token **tokens);

// utils
void		clear_screen(void);
int			check_file_existence(t_token **tokens);
int			is_valid_identifier(const char *str);

// execution
t_cmd		*parse_tokens(char **av);
void		allocate_args_for_cmd(t_cmd *cmd);

// builtins
void		init_execution(t_cmd *cmd_list, t_env_data *ev);
int			ft_echo(char **args);
int			ft_exit(t_env_data *ev, t_cmd *cmd, int fd[4]);
int			ft_cd(char **total_arg);
int			ft_env(t_env *ev);
int			ft_pwd(void);
int			ft_export(t_env_data *env_list, char **args);
int			ft_unset(t_env_data *env_list, char **args);

// builtins_utils
void		init_fd(int fd[6]);
void		execute_builtins(t_cmd *cmd, t_env_data *ev, int fd[4]);
int			count_args_for_cmd(char **tokens);
void		restore_and_cleanup(int fd[6], char **envp, t_cmd *cmd_list);
void		update_exit_status(int status, t_env_data *ev);
void		cleanup_fds(int fd[6], t_cmd *cmd);
int			handle_input_file(t_cmd *cmd, t_env_data *ev, int nums[2]);
int			handle_output_file(t_cmd *cmd, t_env_data *ev, int nums[2],
				int fd[6]);
void		free_fds(int fd[4], int *prev_fd);
void		handle_output_redir(t_cmd *cmd, t_env_data *ev, int fd[6]);
void		execute_child_process(t_cmd *cmd, t_env_data *ev, int fd[6],
				char **envp);
int			process_redirection_tokens(t_cmd *cmd, t_env_data *ev, int fd[6],
				int nums[2]);
void		implement_redir(t_cmd *cmd);
void		setup_redirections(int fd[6], t_cmd *cmd);
void		single_builtin(t_cmd *cmd, t_env_data *ev, int fd[4]);

// commands
void		execute_command(t_cmd *cmd, char **environ, t_env_data *ev);
void		ft_strcpy(char *dst, const char *src);
void		ft_strncpy(char *dst, const char *src, size_t len);
void		ft_strcat(char *dst, const char *src);
char		*find_command_path(char *cmd, char **envp);
int			find_char(char *str, char *charset);
char		**env_list_to_envp(t_env *env_list);
int			count_arg(t_env *tmp);
void		free_exit(char *cmd_path, t_env_data *ev, t_cmd *cmd);
char		*build_command_path(const char *dir, const char *cmd);
char		*get_next_path(char *path, int *index);

// environment
t_env_data	*env_init(char **envp);
void		add_env_node(t_env **head, char *key, char *value, int has_value);
char		*get_env_value(t_env *env_list, char *key);
void		expand_variables(t_token **tokens, t_env_data *env_data);
char		*expand_variable(char *str, t_env_data *env_data);
char		*ft_strjoin_chr(char *s, char c);

// expand_utils
char		*strjoin_char_and_free(char *s, char c);
char		*strjoin_and_free(char *s1, char *s2);
char		*get_value(t_env *env_list, char *key);

// heredoc.c
void		handle_heredoc(char *heredoc_path);
int			process_all_heredocs(t_cmd *cmd_list);
int			create_heredoc(char *limiter, char **heredoc_path);

void		free_env_list(t_env *env_list);
void		free_env_data(t_env_data *env_data);
void		free_args(char **args);
void		free_cmd_list(t_cmd *cmd_list);
void		free_tokens(char **tokens);
void		free_cmd(t_cmd *cmd, int fd[4]);
void		free_cmd_data(t_cmd *cmd, t_env_data *ev);

// redirections
int			handle_input_redirection(char *infile);
int			open_fds(char *outfile, int append);
int			handle_redirection(char *outfile, int append);

#endif
