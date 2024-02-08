NAME		= Minishell

CC			= gcc
UNAME 		:= $(shell uname -s)

CC_FLAGS	= -Wall -Wextra -Werror -g
INCLUDES	= -Iincludes -Ilibft/includes

SRC_DIR		= src
SRC			= main.c lexer/lexer.c
SRCS		= $(addprefix $(SRC_DIR)/, $(SRC))

LIBFT_PATH	= ./libft
LIBFT		= $(LIBFT_PATH)/libft.a
OS_FLASG	=

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
