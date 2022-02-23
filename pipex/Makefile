NAME	=	pipex

CC		=	cc

CFLAGS	=    -Wall -Werror -Wextra


SRCS	=	main.c			\

OBJS	=	${SRCS:.c=.o}

RM		=	rm -f

HEADERS = incl/pipex.h Makefile

%.o:	%.c $(HEADERS)
		${CC} ${CFLAGS} -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS) 
		$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
		@printf	"\e[0;32m[BUILT - $(NAME)]\n\033[0m\e[0m"

clean :
		${RM} -r $(OBJS)
		@printf	"\e[0;31m[DELETED - OBJECTS]\033[0m $<\e\n[0m"

fclean : clean
		${RM} ${NAME}
		@printf	"\e[0;31m[DELETED - ${NAME}]\033[0m \e\n[0m"

re: fclean all

.PHONY : all clean fclean re

.SILENT :