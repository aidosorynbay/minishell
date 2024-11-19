# Compiler and flags
CC			= gcc
CFLAGS		= -Wall -Wextra -Werror -Iinc/ -Ilibft/

# Directories
SRCS_DIR	= srcs
INC_DIR		= inc
OBJS_DIR	= objs
LIBFT_DIR	= libft

# Files and output
NAME		= minishell
SRCS		= $(SRCS_DIR)/main.c $(SRCS_DIR)/tokenization.c
OBJS		= $(SRCS:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o)

# Libraries
LIBS		= -lreadline -L$(LIBFT_DIR) -lft

# Rules
all: $(NAME)

$(NAME): $(OBJS) $(LIBFT_DIR)/libft.a
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBS)

$(LIBFT_DIR)/libft.a:
	$(MAKE) -C $(LIBFT_DIR)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c | $(OBJS_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJS_DIR):
	mkdir -p $(OBJS_DIR)

clean:
	rm -rf $(OBJS_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re bonus
