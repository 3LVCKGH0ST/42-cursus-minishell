NAME = minishell

SRCS = minishell.c \
		handlers.c \
		strings.c \

OBJS = $(SRCS:.c=.o)

FLAGS	=	-Wall -Werror -Wextra -lreadline

all		:	$(NAME)

$(NAME)	:	$(SRCS)
			cc $(FLAGS) $(SRCS) -o $(NAME)

clean	:
		rm -f $(OBJS)

fclean	:	clean
		rm -f $(OBJS) $(NAME)

re		:	fclean all