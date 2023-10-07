NAME = minishell
SRC = main.c
OBJ = $(SRC:.c=.o)

CC = gcc
RM = rm -rf
CFLAGS = -Wall -Wextra -Werror
EXEC = exec
PARSER = parserr
UTILS = utils
BUILTIN = builtin

all: $(NAME)

$(NAME): $(OBJ)
	@make -s -C $(UTILS)
	@make -s -C $(EXEC)
	@make -s -C $(PARSER)
	@make -s -C $(BUILTIN)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(UTILS)/libutils.a $(EXEC)/libexec.a $(PARSER)/libparser.a $(BUILTIN)/libbuiltin.a -lreadline

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	@$(RM) $(OBJ)
	@make clean -s -C $(UTILS)
	@make clean -s -C $(EXEC)
	@make clean -s -C $(PARSER)
	@make clean -s -C $(BUILTIN)

fclean: clean
	@$(RM) $(NAME)
	@make fclean -s -C $(UTILS)
	@make fclean -s -C $(EXEC)
	@make fclean -s -C $(PARSER)
	@make fclean -s -C $(BUILTIN)

re: fclean all

.PHONY: all clean fclean re
