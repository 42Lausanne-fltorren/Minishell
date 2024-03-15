NAME		= Minishell

CC			= gcc
UNAME 		:= $(shell uname -s)

CC_FLAGS	= -Wall -Wextra -Werror -g
INCLUDES	= -Iincludes -Ilibft/includes -lreadline

SRC_DIR		= src
SRC			= main.c \
				lexer/lexer.c lexer/lexer_utils.c lexer/tokenizers.c lexer/tokenizers_simple.c \
				parser/parser.c parser/parser_utils.c \
				expander/expander.c expander/expander_utils.c expander/expander_cmd.c \
				executor/executor.c executor/executor_utils.c \
				builtins/echo.c \
				memory/free.c
SRCS		= $(addprefix $(SRC_DIR)/, $(SRC))

LIBFT_PATH	= ./libft
LIBFT		= $(LIBFT_PATH)/libft.a
OS_FLAGS	=

ifeq ($(UNAME),Linux)
	OS_FLAGS = -Llibft -lft -Wl,-rpath=libft
endif

all: $(NAME)

$(LIBFT):
	make -C $(LIBFT_PATH) bonus so
	cp $(LIBFT_PATH)/libft.so .

$(NAME): $(LIBFT)
	$(CC) $(CC_FLAGS) -o $(NAME) $(SRCS) $(INCLUDES) $(OS_FLAGS)

$(OUT_DIR):
	mkdir -p $(OUT_DIR)

clean:
	make -C $(LIBFT_PATH) clean
	rm -rf $(OUT_DIR)
	rm -rf libft.so

fclean: clean
	make -C $(LIBFT_PATH) fclean
	rm -Rf $(NAME)

re: fclean all

.PHONY: clean fclean re all libft
