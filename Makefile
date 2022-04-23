NAME		:= minishell

PARSING		:=	./mandatory/parsing/ast.c \
				./mandatory/parsing/lexer_0.c \
				./mandatory/parsing/lexer_1.c \
				./mandatory/parsing/lexer_2.c \
				./mandatory/parsing/lexer_3.c \
				./mandatory/parsing/parser_0.c \
				./mandatory/parsing/parser_1.c \
				./mandatory/parsing/parser_2.c \
				./mandatory/parsing/parser_redir.c \
				./mandatory/parsing/expand_2.c \
				./mandatory/parsing/expand.c \
				./mandatory/parsing/expand_utils.c \
				./mandatory/parsing/parser_wildcard.c \
				./mandatory/parsing/print_tree_0.c \
				./mandatory/parsing/print_tree_1.c \
				./mandatory/parsing/free_tree_0.c \
				./mandatory/parsing/free_tree_1.c \
				./mandatory/parsing/token.c	\

BUILDER		:=	./mandatory/builder/builder_0.c \
				./mandatory/builder/builder_1.c \
				./mandatory/builder/print_builder.c \
				./mandatory/builder/free_builder.c\

EXECUTION	:=	./mandatory/execute/execute_0.c \
				./mandatory/execute/execute_1.c \
				./mandatory/execute/execute_utils.c \
				./mandatory/execute/path_patch.c \
				./mandatory/execute/exec_sh_file.c \
				./mandatory/execute/iter_builder.c \
				./mandatory/signals/signals.c \
				./mandatory/execute/_cd.c \
				./mandatory/execute/_exit.c \
				./mandatory/execute/_export.c \
				./mandatory/execute/_echo.c \
				./mandatory/execute/_env.c \
				./mandatory/execute/_env_utils.c \
				./mandatory/execute/_pwd.c \
				./mandatory/execute/_unset.c \
				./mandatory/execute/strings.c \


PARSING_B		:=	./bonus/parsing/ast_bonus.c \
				./bonus/parsing/lexer_0_bonus.c \
				./bonus/parsing/lexer_1_bonus.c \
				./bonus/parsing/lexer_2_bonus.c \
				./bonus/parsing/lexer_3_bonus.c \
				./bonus/parsing/parser_0_bonus.c \
				./bonus/parsing/parser_1_bonus.c \
				./bonus/parsing/parser_2_bonus.c \
				./bonus/parsing/parser_redir_bonus.c \
				./bonus/parsing/expand_2_bonus.c \
				./bonus/parsing/expand_bonus.c \
				./bonus/parsing/expand_utils_bonus.c \
				./bonus/parsing/parser_wildcard_bonus.c \
				./bonus/parsing/print_tree_0_bonus.c \
				./bonus/parsing/print_tree_1_bonus.c \
				./bonus/parsing/free_tree_0_bonus.c \
				./bonus/parsing/free_tree_1_bonus.c \
				./bonus/parsing/token_bonus.c	\

BUILDER_B		:=	./bonus/builder/builder_0_bonus.c \
				./bonus/builder/builder_1_bonus.c \
				./bonus/builder/print_builder_bonus.c \
				./bonus/builder/free_builder_bonus.c\

EXECUTION_B	:=	./bonus/execute/execute_0_bonus.c \
				./bonus/execute/execute_1_bonus.c \
				./bonus/execute/execute_utils_bonus.c \
				./bonus/execute/path_patch_bonus.c \
				./bonus/execute/exec_sh_file_bonus.c \
				./bonus/execute/iter_builder_bonus.c \
				./bonus/signals/signals_bonus.c \
				./bonus/execute/_cd_bonus.c \
				./bonus/execute/_exit_bonus.c \
				./bonus/execute/_export_bonus.c \
				./bonus/execute/_echo_bonus.c \
				./bonus/execute/_env_bonus.c \
				./bonus/execute/_env_utils_bonus.c \
				./bonus/execute/_pwd_bonus.c \
				./bonus/execute/_unset_bonus.c \
				./bonus/execute/strings_bonus.c \


DLINKEDLIST	:=	./double_linked_list/s_d_list_0.c \
				./double_linked_list/s_d_list_1.c \
				./double_linked_list/s_d_list_3.c \

LIBFTDIR	:= ./libft/
LIBFT		:= ./libft/libft.a

SRC			:=  ./mandatory/minishell.c ./mandatory/utils.c $(PARSING) $(BUILDER) $(EXECUTION)  $(DLINKEDLIST)
SRCB		:=  ./bonus/minishell_bonus.c ./bonus/utils_bonus.c $(PARSING_B) $(BUILDER_B) $(EXECUTION_B)  $(DLINKEDLIST)
OBJ			:= $(patsubst %.c, %.o, $(SRC)) 
OBJB		:= $(patsubst %.c, %.o, $(SRCB)) 
CC			:= gcc
#RDLINE		:= -lreadline -L/Users/mbalagui/.brew/opt/readline/lib 
#FLAGS		:= -Wall -Wextra -Werror -I/Users/mbalagui/.brew/opt/readline/include  -g -fsanitize=address 
RDLINE		:= -lreadline -L/goinfre/asouinia/homebrew/opt/readline/lib 
FLAGS		:= -Wall -Wextra -Werror -I/goinfre/asouinia/homebrew/opt/readline/include  -g  -fsanitize=address 
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
	@$(CC)  $(FLAGS)  $(RDLINE) $(OBJB) $(LIBFT) -o $(NAME) 

t: $(NAME)
	./$(NAME)

s: bonus
	./$(NAME)

res: fclean s 