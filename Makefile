NAME	=	minishell
CC		=	gcc
CFLAGS	:=	-Wall -Werror -Wextra  -g -fsanitize=address 

SRCS	=	main.c										\
			srcs/loop.c									\
			srcs/utils.c								\
			srcs/signals.c								\
			srcs/builtin/echo.c							\
			srcs/builtin/pwd.c							\
			srcs/builtin/cd.c							\
			srcs/builtin/exit.c							\
			srcs/builtin/env.c							\
			srcs/builtin/unset.c						\
			srcs/builtin/export/export.c				\
			srcs/builtin/export/utils_export.c			\
			srcs/builtin/export/env_manip.c				\
			srcs/builtin/export/alloc_env.c				\
			srcs/parser/parse.c							\
			srcs/parser/parse_quote.c					\
			srcs/parser/utils.c							\
			srcs/parser/join.c							\
			srcs/parser/redir_utils.c					\
			srcs/parser/redir.c							\
			srcs/parser/split.c							\
			srcs/parser/split_utils.c					\
			srcs/pipex/pipex.c							\
			srcs/pipex/srcs/exec.c						\
			srcs/pipex/srcs/utils.c						\
			srcs/redir/redir.c 							\
			srcs/redir/utils.c 							\

OBJS	=	${SRCS:.c=.o}
OBJS_DIR	= objs/
OBJECTS_PREFIXED = $(addprefix $(OBJS_DIR), $(OBJS))
RL_LIB_DIR := -L$(shell brew --prefix readline)/lib
RL_INC_DIR := -I$(shell brew --prefix readline)/include

RM		=	rm -f

all: libft $(NAME)

$(OBJS_DIR)%.o:	%.c incl/minishell.h Makefile libft/libft.a
		@mkdir -p $(OBJS_DIR)
		@mkdir -p $(OBJS_DIR)srcs/pipex
		@mkdir -p $(OBJS_DIR)srcs/pipex/srcs
		@mkdir -p $(OBJS_DIR)srcs/redir
		@mkdir -p $(OBJS_DIR)srcs
		@mkdir -p $(OBJS_DIR)srcs/parser
		@mkdir -p $(OBJS_DIR)srcs/builtin
		@mkdir -p $(OBJS_DIR)srcs/builtin/export
		$(CC) $(RL_INC_DIR) $(CFLAGS) -c $< -o $@
		printf	"\033[2K\r\033[0;33m[BUILD - $(NAME)]\033[0m $<\e[0m"

$(NAME): $(OBJECTS_PREFIXED)
		$(CC) $(CFLAGS) $(RL_LIB_DIR) $(OBJECTS_PREFIXED) -l readline -L libft -l ft -o $(NAME)
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