# Compiler and flags
CC          = cc
CFLAGS      = -Wall -Wextra -Werror -g3 -fsanitize=address -Iinc/ -Ilibft/

# Directories
SRCS_DIR    = srcs
TOKENS_DIR     = $(SRCS_DIR)/tokens
INC_DIR     = inc
OBJS_DIR    = objs
LIBFT_DIR   = libft
EXECUTION_DIR = $(SRCS_DIR)/execution
BUILTINS_DIR  = $(EXECUTION_DIR)/builtins

# Files and output
NAME        = minishell
SRCS        = $(SRCS_DIR)/main.c \
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
			  $(BUILTINS_DIR)/builtins.c \
			  $(BUILTINS_DIR)/cd.c \
			  $(BUILTINS_DIR)/echo.c \
			  $(BUILTINS_DIR)/pwd.c \
			  $(BUILTINS_DIR)/exit.c \
			  $(TOKENS_DIR)/trimming.c 
			#   $(EXECUTION_DIR)/converter.c \
			#   $(EXECUTION_DIR)/token_parser.c \
			#   $(BUILTINS_DIR)/builtins.c \
			#   $(BUILTINS_DIR)/cd.c \
			#   $(BUILTINS_DIR)/echo.c \
			#   $(BUILTINS_DIR)/exit.c 

OBJS        = $(SRCS:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o)

# Libraries
LIBS        = -lreadline -L$(LIBFT_DIR) -lft

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
