NAME= minishell
CC= cc
FLAGS= -Wall -Wextra -Werror -fsanitize=address -g
SRC= minishell.c utils.c depart.c change_type.c env.c expand.c link.c syntaxe_err.c

HEADERS_DIRECTORY = ./
HEADERS_LIST = minishell.h
HEADERS = $(addprefix $(HEADERS_DIRECTORY), $(HEADERS_LIST))

INCLUDES = -I$(HEADERS_DIRECTORY) 

OBJ = $(SRC:.c=.o)

all : lib $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(INCLUDES) $(FLAGS) $(OBJ) ./libft/libft.a -o $@ -lreadline 

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
