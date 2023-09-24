GREEN = \033[0;32m
RED = \033[0;31m
NC = \033[0m

NAME = libparser.a
SRC = error.c free_tokens.c ft_memcpy.c ft_strchr.c lexer.c parser.c pipe_counter.c start.c
OBJ = $(SRC:.c=.o)

CC = gcc
AR = ar rc
RM = rm -rf
CFLAGS = -Wall -Werror -Wextra -I..
LDFLAGS = -lreadline

all: $(NAME)

$(NAME): $(OBJ)
	@$(AR) $(NAME) $(OBJ)
	@echo "$(GREEN)$(NAME) is ready!$(NC)"

clean:
	@$(RM) $(OBJ)
	@echo "$(RED)Cleaned object files.$(NC)"

fclean: clean
	@$(RM) $(NAME)
	@echo "$(RED)Removed $(NAME) static library.$(NC)"

re: fclean all

.PHONY: all clean fclean re
