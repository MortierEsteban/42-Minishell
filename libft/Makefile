NAME	= 	libft.a
CC		=	gcc
CFLAGS	=	-Wall -Werror -Wextra
SRCS	= 	ft_char_str/ft_atoi.c \
			ft_char_str/ft_strchr.c \
			ft_char_str/ft_strdup.c \
			ft_char_str/ft_strlcat.c \
			ft_char_str/ft_strlcpy.c \
			ft_char_str/ft_strlen.c \
			ft_char_str/ft_strncmp.c \
			ft_char_str/ft_strnstr.c \
			ft_char_str/ft_strrchr.c \
			ft_char_str/ft_tolower.c \
			ft_char_str/ft_toupper.c \
			ft_char_str/ft_substr.c \
			ft_char_str/ft_strjoin.c \
			ft_char_str/ft_strtrim.c \
			ft_char_str/ft_split.c \
			ft_char_str/ft_itoa.c \
			ft_char_str/ft_strmapi.c \
			ft_char_str/ft_striteri.c \
			ft_is/ft_isalnum.c	\
			ft_is/ft_isalpha.c	\
			ft_is/ft_isascii.c	\
			ft_is/ft_isspace.c	\
			ft_is/ft_isdigit.c	\
			ft_is/ft_isprint.c	\
			ft_is/ft_isupper.c	\
			ft_is/ft_islower.c 	\
			ft_mem/ft_bzero.c	\
			ft_mem/ft_calloc.c	\
			ft_mem/ft_memchr.c \
			ft_mem/ft_memcmp.c \
			ft_mem/ft_memcpy.c \
			ft_mem/ft_memmove.c \
			ft_mem/ft_memset.c \
			ft_mem/ft_gc_malloc.c \
			ft_printf/srcs/ft_printf.c \
			ft_printf/srcs/ft_process.c \
			ft_printf/srcs/ft_printf_put.c \
			ft_put/ft_putchar_fd.c \
			ft_put/ft_putstr_fd.c \
			ft_put/ft_putendl_fd.c \
			ft_put/ft_putnbr_fd.c \
			ft_lst/ft_lstnew.c \
			ft_lst/ft_lstadd_front.c \
			ft_lst/ft_lstsize.c \
			ft_lst/ft_lstlast.c \
			ft_lst/ft_lstadd_back.c \
			ft_lst/ft_lstdelone.c \
			ft_lst/ft_lstclear.c \
			ft_lst/ft_lstiter.c \
			ft_lst/ft_lstmap.c \
			ft_gnl/get_next_line.c \
			ft_gnl/get_next_line_utils.c

OBJS	= ${SRCS:.c=.o}

RM		= rm -f

%.o:	%.c libft.h Makefile ft_printf/include/ft_printf.h ft_gnl/get_next_line.h
		$(CC) $(CFLAGS) -c $< -o $@
		@printf	"\033[2K\r\033[0;33m[BUILD - $(NAME)]\033[0m $<\e[0m"

all : $(NAME)

$(NAME): $(OBJS)
		ar crs $(NAME) $(OBJS)
		@printf "\033[2K\r\033[0;32m[END]\033[0m $(NAME)\e[0m"

clean :
		$(RM) $(OBJS) $(OBJS_BONUS)
		@printf "\033[2K\r\033[0;31m.o files deleted.\n\e[0m"

fclean : clean
		$(RM) $(NAME)
		@printf "\033[0;31m$(NAME) deleted.\n\e[0m"

re: fclean all

.PHONY : help all clean fclean re

.SILENT: