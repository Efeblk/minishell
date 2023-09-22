
GREEN = \033[0;32m
RED = \033[0;31m
NC = \033[0m

NAME = minishell
SRC = ft_split.c ft_strdup.c parser.c ft_substr.c ft_strlen.c ft_strchr.c quote_counter.c main.c lexer.c ft_realloc.c
OBJ = $(SRC:.c=.o)

CC = gcc
RM = rm -rf
CFLAGS = -Wall -Werror -Wextra
LDFLAGS = -lreadline


all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) $(LDFLAGS) -o $(NAME)
	@echo "$(GREEN)$(NAME) is ready!$(NC)"

clean:
	@$(RM) $(OBJ)
	@echo "$(RED)Cleaned object files.$(NC)"

fclean: clean
	@$(RM) $(NAME)
	@echo "$(RED)Removed $(NAME) executable.$(NC)"

re: fclean all

.PHONY: all clean fclean re



