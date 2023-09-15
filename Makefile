NAME            =   minishell

SRC				=	ft_split.c ft_strdup.c env.c parser.c ft_substr.c ft_strlen.c


OBJ = $(SRC:.c=.o)

CC				=	gcc
RM 				=	rm -rf
CFLAGS			= 	-Wall -Werror -Wextra

all : $(NAME)

$(NAME) : $(OBJ)
	@$(CC) $(FLAGS) $(OBJ) -o $(NAME)

clean:
	@$(RM) $(OBJ)

fclean: clean
	@$(RM) $(NAME)

re : fclean all

.PHONY: all fclean re 