NAME		:= minishell

PARSING		:=	./mandatory/parsing/ast.c \
				./mandatory/parsing/lexer_0.c \
				./mandatory/parsing/lexer_1.c \
				./mandatory/parsing/lexer_2.c \
				./mandatory/parsing/lexer_3.c \
				./mandatory/parsing/parser_0.c \
				./mandatory/parsing/parser_1.c \
				./mandatory/parsing/parser_2.c \
				./mandatory/parsing/print_tree_0.c \
				./mandatory/parsing/print_tree_1.c \
				./mandatory/parsing/free_tree_0.c \
				./mandatory/parsing/free_tree_1.c \
				./mandatory/parsing/token.c	\

BUILDER		:=	./mandatory/builder/builder_0.c \
				./mandatory/builder/builder_1.c \
				./mandatory/builder/builder_expand.c \
				./mandatory/builder/print_builder.c \
				./mandatory/builder/free_builder.c\

EXECUTION	:=	./mandatory/execute/execute_0.c \
				./mandatory/execute/execute_1.c \
				./mandatory/execute/iter_builder.c \
				./mandatory/signals/signals.c \
				./mandatory/execute/_cd.c \
				./mandatory/execute/_echo.c \
				./mandatory/execute/_env.c \
				./mandatory/execute/_env_utils.c \
				./mandatory/execute/_pwd.c \
				./mandatory/execute/_unset.c \
				./mandatory/execute/strings.c \

PARSING_B	:= 	./bonus/parsing/ast_bonus.c \
				./bonus/parsing/lexer_bonus.c \
				./bonus/parsing/lexer1_bonus.c \
				./bonus/parsing/parser_bonus.c \
				./bonus/parsing/token_bonus.c \

EXECUTION_B	:=

DLINKEDLIST	:=	./double_linked_list/s_d_list_0.c \
				./double_linked_list/s_d_list_1.c \

LIBFTDIR	:= ./libft/
LIBFT		:= ./libft/libft.a

SRC			:=  ./mandatory/minishell.c $(PARSING) $(BUILDER) $(EXECUTION)  $(DLINKEDLIST)
SRCB		:=   ./bonus/minishell_bonus.c  $(PARSING_B) $(EXECUTION_B)  $(DLINKEDLIST)
OBJ			:= $(patsubst %.c, %.o, $(SRC)) 
OBJB		:= $(patsubst %.c, %.o, $(SRCB)) 
RDLINE		:= -lreadline -L/goinfre/asouinia/homebrew/opt/readline/lib 
CC			:= gcc
FLAGS		:= -Wall -Wextra -Werror -I/goinfre/asouinia/homebrew/opt/readline/include  -g -fsanitize=address 


.PHONY: all clean fclean re bonus

all: $(NAME)
$(NAME): $(OBJ) $(LIBFT)
	@$(CC)  $(FLAGS)  $(RDLINE) $(OBJ) $(LIBFT) -o $(NAME) 
%.o: %.c
	$(CC) $(FLAGS) -c $<  -o $@

$(LIBFT):
	@make -C $(LIBFTDIR)

clean:
	@make -C $(LIBFTDIR) fclean
	@rm -f $(OBJ) $(OBJB)

fclean: clean
	@rm -f $(NAME)

re: fclean all

bonus: $(OBJB) $(LIBFT)
	@$(CC) $(FLAGS) $(OBJB) $(LIBFT) -o $(NAME)

t: $(NAME)
	./$(NAME)

s: bonus
	./$(NAME)
