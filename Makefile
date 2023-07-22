NAME= minishell
CC= cc
FLAGS= -Wall -Wextra -Werror -fsanitize=address -g

SRC = ./parsing/minishell.c ./parsing/utils.c ./parsing/depart.c ./parsing/change_type.c ./parsing/env.c ./parsing/expand.c \
	./parsing/link.c ./parsing/syntaxe_err.c ./parsing/division.c ./parsing/suite_div.c ./parsing/ft_free.c ./parsing/s_expand.c \
	./parsing/redirect.c ./parsing/final_list.c ./parsing/signals.c ./parsing/herdoc.c ./parsing/parsing.c\
	./execution/exec.c ./execution/exec_utils.c \
	./execution/pipes.c ./execution/pipe_utils.c \
	./execution/builtins/echo.c ./execution/builtins/pwd.c \
	./execution/builtins/env_n.c ./execution/builtins/built.c \
	./execution/builtins/cd.c ./execution/builtins/export.c \
	./execution/builtins/unset.c

HEADERS_DIRECTORY = ./
HEADERS_LIST = minishell.h
HEADERS = $(addprefix $(HEADERS_DIRECTORY), $(HEADERS_LIST))

INCLUDES = -I$(HEADERS_DIRECTORY) -I/Users/$(USER)/.brew/opt/readline/include

OBJ = $(SRC:.c=.o)

all : lib $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(INCLUDES) $(FLAGS) $(OBJ) ./libft/libft.a  -o $@ -lreadline -L/Users/$(USER)/.brew/opt/readline/lib

%.o : %.c $(HEADERS)
	$(CC) $(FLAGS) -c $(INCLUDES) $< -o $@ 

lib : 
	make -C libft

clean :
	make clean -C libft
	rm -f $(OBJ)

fclean : clean
	make fclean -C libft
	rm -f $(NAME)

re : fclean all

.phony : all clean fclean re 
