NAME= minishell
CC= CC
FLAGS= -Wall -Wextra -Werror -lreadline 
SRC= minishell.c utils.c depart.c exemples.c env.c expand.c

HEADERS_DIRECTORY = ./
HEADERS_LIST = minishell.h
HEADERS = $(addprefix $(HEADERS_DIRECTORY), $(HEADERS_LIST))

INCLUDES = -I$(HEADERS_DIRECTORY) ./libft/libft.a

OBJ = $(SRC:.c=.o)

all : lib $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(INCLUDES) $(FLAGS) $(OBJ) -o $@ 

%.o : %.c $(HEADERS)
	$(CC) $(INCLUDES) $(FLAGS) $< -o $@ 

lib : 
	make -C libft

clean : 	
	rm -f $(OBJ)

fclean : clean
	rm -f $(NAME)

re : fclean all

.phony : all clean fclean re 
