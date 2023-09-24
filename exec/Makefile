GREEN = \033[0;32m
RED = \033[0;31m
NC = \033[0m

LIB_NAME = libexec.a
MAIN_NAME = minishell
SRC = executor.c find_env.c input_commands.c exec_utils.c
OBJ = $(SRC:.c=.o)

CC = gcc
AR = ar rc
RM = rm -rf
CFLAGS = -Wall -Werror -Wextra -I..
LDFLAGS = -lreadline

all: $(LIB_NAME) $(MAIN_NAME)

$(LIB_NAME): $(OBJ)
	@$(AR) $(LIB_NAME) $(OBJ)
	@echo "$(GREEN)$(LIB_NAME) is ready!$(NC)"

$(MAIN_NAME): $(LIB_NAME) $(MAIN_NAME).c
	@$(CC) $(CFLAGS) $(MAIN_NAME).c -o $(MAIN_NAME) -L. -lexec $(LDFLAGS)
	@echo "$(GREEN)$(MAIN_NAME) is ready!$(NC)"

clean:
	@$(RM) $(OBJ)
	@echo "$(RED)Cleaned object files.$(NC)"

fclean: clean
	@$(RM) $(LIB_NAME) $(MAIN_NAME)
	@echo "$(RED)Removed $(LIB_NAME) static library and $(MAIN_NAME) executable.$(NC)"

re: fclean all

.PHONY: all clean fclean re
