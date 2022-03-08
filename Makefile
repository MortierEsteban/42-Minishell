NAME	=	minishell
CC		=	gcc
CFLAGS	=	-Wall -Werror -Wextra #-g -fsanitize=address

SRCS	=	main.c						\
			srcs/loop.c					\
			srcs/utils.c				\
			srcs/builtin/echo.c			\
			srcs/builtin/pwd.c			\
			srcs/builtin/cd.c			\
			srcs/builtin/export.c		\
			srcs/parser/parse.c			\
			srcs/parser/parse_quote.c	\
			srcs/parser/utils.c			\
			srcs/parser/split.c			\
			srcs/parser/split_utils.c	\
			pipex/pipex.c				\
			pipex/srcs/exec.c			\
			pipex/srcs/utils.c			\

OBJS	=	${SRCS:.c=.o}
OBJS_DIR	= objs/
OBJECTS_PREFIXED = $(addprefix $(OBJS_DIR), $(OBJS))

RM		=	rm -f

all: libft $(NAME)

$(OBJS_DIR)%.o:	%.c incl/minishell.h Makefile libft/libft.a
		@mkdir -p $(OBJS_DIR)
		@mkdir -p $(OBJS_DIR)pipex
		@mkdir -p $(OBJS_DIR)pipex/srcs
		@mkdir -p $(OBJS_DIR)srcs
		@mkdir -p $(OBJS_DIR)srcs/parser
		@mkdir -p $(OBJS_DIR)srcs/builtin
		$(CC) $(CFLAGS) -c $< -o $@
		printf	"\033[2K\r\033[0;33m[BUILD - $(NAME)]\033[0m $<\e[0m"

$(NAME): $(OBJECTS_PREFIXED)
		$(CC) $(CFLAGS) $(OBJECTS_PREFIXED) -l readline -L libft -l ft -o $(NAME)
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