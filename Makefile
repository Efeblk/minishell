NAME = minishell
SRC = main.c
OBJ = $(SRC:.c=.o)

CC = gcc
RM = rm -rf
CFLAGS = -Wall -Wextra -Werror 
EXEC = exec
PARSER = parserr
UTILS = utils

all: $(NAME)

$(NAME): $(OBJ)
	@make -s -C $(UTILS)
	@make -s -C $(EXEC)
	@make -s -C $(PARSER)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(UTILS)/libutils.a $(EXEC)/libexec.a $(PARSER)/libparser.a -lreadline

clean:
	@$(RM) $(OBJ)
	@make clean -s -C $(UTILS)
	@make clean -s -C $(EXEC)
	@make clean -s -C $(PARSER)

fclean: clean
	@$(RM) $(NAME)
	@make fclean -s -C $(UTILS)
	@make fclean -s -C $(EXEC)
	@make fclean -s -C $(PARSER)

re: fclean all

.PHONY: all clean fclean re