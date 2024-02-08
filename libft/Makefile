CC			:= gcc
CFLAGS		:= -Wall -Wextra -Werror -g -Iincludes
NAME		:= libft.a
SRCS		:= char/ft_isalnum.c \
				char/ft_isalpha.c \
				char/ft_isascii.c \
				char/ft_isdigit.c \
				char/ft_isprint.c \
				char/ft_tolower.c \
				char/ft_toupper.c \
				ft_printf/ft_nb_converters.c \
				ft_printf/ft_printf.c \
				ft_printf/ft_ptr_converters.c \
				ft_printf/ft_str_converters.c \
				ft_printf/ft_strutils.c \
				ft_printf/ft_utils.c \
				io/ft_putchar_fd.c \
				io/ft_putendl_fd.c \
				io/ft_putnbr_fd.c \
				io/ft_putstr_fd.c \
				list/ft_lstadd_back_bonus.c \
				list/ft_lstadd_front_bonus.c \
				list/ft_lstclear_bonus.c \
				list/ft_lstdelone_bonus.c \
				list/ft_lstiter_bonus.c \
				list/ft_lstlast_bonus.c \
				list/ft_lstmap_bonus.c \
				list/ft_lstnew_bonus.c \
				list/ft_lstsize_bonus.c \
				math/ft_max.c \
				mem/ft_bzero.c \
				mem/ft_calloc.c \
				mem/ft_memchr.c \
				mem/ft_memcmp.c \
				mem/ft_memcpy.c \
				mem/ft_memmove.c \
				mem/ft_memset.c \
				str/ft_atoi.c \
				str/ft_itoa.c \
				str/ft_itoa_base.c \
				str/ft_itoau.c \
				math/ft_min.c \
				str/ft_split.c \
				str/ft_strchr.c \
				str/ft_strdup.c \
				str/ft_striteri.c \
				str/ft_strjoin.c \
				str/ft_strlcat.c \
				str/ft_strlcpy.c \
				str/ft_strlen.c \
				str/ft_strmapi.c \
				str/ft_strncmp.c \
				str/ft_strndup.c \
				str/ft_strnstr.c \
				str/ft_strrchr.c \
				str/ft_strtrim.c \
				str/ft_substr.c \
				char/ft_isspace.c
OBJS		:= ${SRCS:.c=.o}

%.o	: %.c \
	$(CC) $(INCLUDES) $(CFLAGS) -c $< -o $@

${NAME}	: ${OBJS}
	ar -rc ${NAME} ${OBJS}

all		: ${NAME}

clean	:
	rm -f ${OBJS}

fclean	: clean
	rm -f ${NAME}
	rm -f a.out
	rm -f libft.so

re		: fclean all

bonus	: all

so:
	$(CC) $(INCS) -nostartfiles -fPIC $(CFLAGS) $(SRCS)
	gcc -nostartfiles -shared -o libft.so $(OBJS)
