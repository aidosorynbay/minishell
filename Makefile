# Compiler and flags
CC			= cc
CFLAGS		= -Wall -Wextra -Werror -g3 -fsanitize=address -Iinc/ -Ilibft/

# Directories
SRCS_DIR	= srcs
TOKENS_DIR	= $(SRCS_DIR)/tokens
INC_DIR		= inc
OBJS_DIR	= objs
LIBFT_DIR	= libft

# Files and output
NAME		= minishell
SRCS		= $(SRCS_DIR)/main.c \
			  $(TOKENS_DIR)/tokenization.c \
			  $(TOKENS_DIR)/token_utils.c \
			  $(TOKENS_DIR)/syntax_check.c \
			  $(TOKENS_DIR)/more_utils.c

OBJS		= $(SRCS:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o)

# Libraries
LIBS		= -lreadline -L$(LIBFT_DIR) -lft

# Rules
all: $(NAME)

$(NAME): $(OBJS) $(LIBFT_DIR)/libft.a
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBS)

$(LIBFT_DIR)/libft.a:
	$(MAKE) -C $(LIBFT_DIR)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(dir $@) # Ensure the output directory exists
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re bonus

