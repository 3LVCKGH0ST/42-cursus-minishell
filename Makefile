NAME	:= minishell
<<<<<<< HEAD
SRC		:=   handlers.c  strings.c minishell.c parse.c quotes.c ft_memcpy.c ft_strdup.c ft_strtrim.c multipipes.c ft_split.c ft_substr.c echo.c
=======
SRC		:=   handlers.c  strings.c minishell.c parse.c quotes.c ft_memcpy.c ft_strdup.c ft_strtrim.c multipipes.c here_doc_check.c echo.c
>>>>>>> 6599f7574c849f617421f455d70ecb1211a8a238
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
