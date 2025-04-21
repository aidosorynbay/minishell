# Compiler and flags
CC          = cc
# CFLAGS      = -Wall -Wextra -Werror -g3 -fsanitize=address -Ilibft -I./ -I/opt/vagrant/embedded/include/readline -I/opt/vagrant/embedded/include
CFLAGS      = -Wall -Wextra -Werror -g3 -Ilibft -I./ -I/opt/vagrant/embedded/include/readline -I/opt/vagrant/embedded/include
CFLAGS += -Iinc
READLINE    = -L/opt/vagrant/embedded/lib/ -lreadline

# Directories
SRCS_DIR    = srcs
TOKENS_DIR     = $(SRCS_DIR)/tokens
INC_DIR     = inc
OBJS_DIR    = objs
LIBFT_DIR   = libft
EXECUTION_DIR = $(SRCS_DIR)/execution
BUILTINS_DIR  = $(EXECUTION_DIR)/builtins
COMMANDS_DIR  = $(EXECUTION_DIR)/commands
ENVIRONMENT_DIR  = $(EXECUTION_DIR)/environment

# Files and output
NAME        = minishell
SRCS        = $(SRCS_DIR)/main.c \
			  $(SRCS_DIR)/free.c \
			  $(SRCS_DIR)/free_utils.c \
              $(TOKENS_DIR)/tokenization.c \
              $(TOKENS_DIR)/token_utils.c \
              $(TOKENS_DIR)/syntax_check.c \
              $(TOKENS_DIR)/more_utils.c \
              $(TOKENS_DIR)/syntax_check_utils.c \
              $(TOKENS_DIR)/utils.c \
              $(TOKENS_DIR)/assign_type_utils.c \
              $(TOKENS_DIR)/assign_type.c \
		  $(EXECUTION_DIR)/converter.c \
		  $(EXECUTION_DIR)/token_parser.c \
		  $(COMMANDS_DIR)/commands.c \
		  $(COMMANDS_DIR)/commands_utils.c \
		  $(COMMANDS_DIR)/commands_utils_2.c \
		  $(BUILTINS_DIR)/builtins.c \
		  $(BUILTINS_DIR)/builtins_utils.c \
		  $(BUILTINS_DIR)/cd.c \
		  $(BUILTINS_DIR)/echo.c \
		  $(BUILTINS_DIR)/pwd.c \
		  $(BUILTINS_DIR)/exit.c \
		  $(BUILTINS_DIR)/env.c \
		  $(BUILTINS_DIR)/unset.c \
		  $(BUILTINS_DIR)/heredoc.c \
		  $(BUILTINS_DIR)/redirections.c \
		  $(TOKENS_DIR)/trimming.c \
		  $(BUILTINS_DIR)/export.c \
		  $(BUILTINS_DIR)/export_utils.c \
		  $(ENVIRONMENT_DIR)/env_init.c \
		  $(ENVIRONMENT_DIR)/expand.c \
		  $(ENVIRONMENT_DIR)/expand_utils.c

OBJS        = $(SRCS:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o)

# Libraries
LIBS        = $(READLINE) -L$(LIBFT_DIR) -lft

# Ascii art
START_ART   = "🌟 Starting compilation of Minishell! 🌟"
END_ART     = "\n🎉 Minishell is ready to run! 🎉"
CLEAN_ART   = "🧹 Cleaning up build files..."
FCLEAN_ART  = "🔥 Removing everything, including the executable..."
RE_ART      = "🔄 Rebuilded everything from scratch!"

# Rules
all: $(NAME)

$(NAME): $(OBJS) $(LIBFT_DIR)/libft.a
	@echo $(START_ART)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBS)
	@echo $(END_ART)

$(LIBFT_DIR)/libft.a:
	@echo "📦 Building Libft library..."
	@$(MAKE) -C $(LIBFT_DIR) --silent

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(dir $@) # Ensure the output directory exists
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "🔧 Compiled $<"

clean:
	@echo $(CLEAN_ART)
	@rm -rf $(OBJS_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean --silent

fclean: clean
	@echo $(FCLEAN_ART)
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean --silent

re: fclean all
	@echo $(RE_ART)

.PHONY: all clean fclean re
