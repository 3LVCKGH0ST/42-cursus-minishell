NAME	:= minishell
SRC		:=  main.c  minishell.c handlers.c  strings.c
SRCB	:=  
OBJ		:= $(patsubst %.c, %.o, $(SRC)) 
OBJB	:= $(patsubst %.c, %.o, $(SRCB)) 
CC		:= gcc
FLAGS	:= -Wall -Wextra -Werror  -g -fsanitize=address 

.PHONY: all clean fclean re bonus

all: $(NAME)
$(NAME): $(OBJ)
	@$(CC) $(FLAGS) -lreadline $(OBJ) -o $(NAME)
%.o: %.c
	$(CC) $(FLAGS) -c $<  -o $@
clean:
	@rm -f $(OBJ) $(OBJB)
fclean: clean
	@rm -f $(NAME)
re: fclean all
bonus: $(OBJB)
	@$(CC) $(FLAGS) $(OBJB) -o $(NAME)

t: $(NAME)
	./$(NAME)
