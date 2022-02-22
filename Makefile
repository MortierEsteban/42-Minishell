NAME	=	minishell
CC		=	gcc
CFLAGS	=	-Wall -Werror -Wextra -g

SRCS	=	main.c \
			srcs/loop.c \
			srcs/utils.c \
			srcs/builtin/echo.c \
			srcs/builtin/pwd.c \
			srcs/builtin/cd.c \
			srcs/builtin/export.c \
			srcs/parser/parse.c \
			srcs/parser/utils.c

OBJS	=	${SRCS:.c=.o}

RM		=	rm -f

%.o:	%.c incl/minishell.h Makefile
		${CC} ${CFLAGS} -c $< -o $@
		printf	"\033[2K\r\033[0;33m[BUILD - $(NAME)]\033[0m $<\e[0m"

$(NAME): $(OBJS)
		@make -C ./libft/
		$(CC) $(OBJS) -L libft -l ft -o $(NAME)
		@printf "\033[2K\r\033[0;32m[END]\033[0m $(NAME)\e[0m"

all: $(NAME)

clean :
		@make -C ./libft/ clean
		${RM} ${OBJS} ${OBJS_BONUS}
		@printf "\033[2K\r\033[0;31m.o files deleted.\n\e[0m"

fclean : clean
		@make -C ./libft/ fclean
		${RM} ${NAME}
		@printf "\033[0;31m$(NAME) deleted.\n\e[0m"

re: fclean all

.PHONY : all clean fclean re

.SILENT: