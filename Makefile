NAME	=	minishell
CC		=	gcc
CFLAGS	=	-Wall -Werror -Wextra #-g -fsanitize=address

SRCS	=	main.c \
			srcs/loop.c \
			srcs/utils.c \
			srcs/builtin/echo.c \
			srcs/builtin/pwd.c \
			srcs/builtin/cd.c \
			srcs/builtin/export.c \
			srcs/parser/parse.c \
			srcs/parser/split.c \
			srcs/parser/utils.c

OBJS	=	${SRCS:.c=.o}

RM		=	rm -f

all: libft $(NAME)

%.o:	%.c incl/minishell.h Makefile libft/libft.a
		$(CC) $(CFLAGS) -c $< -o $@
		printf	"\033[2K\r\033[0;33m[BUILD - $(NAME)]\033[0m $<\e[0m"

$(NAME): $(OBJS)
		$(CC) $(CFLAGS) $(OBJS) -l readline -L libft -l ft -o $(NAME)
		@printf "\033[2K\r\033[0;32m[END]\033[0m $(NAME)\e[0m"

libft:
		make -C ./libft

clean :
		@make -C ./libft/ clean
		${RM} ${OBJS} ${OBJS_BONUS}
		@printf "\033[2K\r\033[0;31m.o files deleted.\n\e[0m"

fclean : clean
		@make -C ./libft/ fclean
		${RM} ${NAME}
		@printf "\033[0;31m$(NAME) deleted.\n\e[0m"

re: fclean all

.PHONY : libft all clean fclean re

.SILENT: