# Name of the final executable
NAME = minishell

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror

# Directories for components
EXEC_DIR = exec
PARSER_DIR = parserr
UTILS_DIR = utils

# Output directories for libraries
EXEC_OUT = $(EXEC_DIR)/libexec.a
PARSER_OUT = $(PARSER_DIR)/libparser.a
UTILS_OUT = $(UTILS_DIR)/libutils.a

# Source files and object files (add your source files here)
SRCS = main.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) $(EXEC_OUT) $(PARSER_OUT) $(UTILS_OUT)
	@$(CC) $(CFLAGS) -o $@ $(OBJS) $(EXEC_OUT) $(PARSER_OUT) $(UTILS_OUT) -lreadline

$(EXEC_OUT):
	@make -s -C $(EXEC_DIR)

$(PARSER_OUT):
	@make -s -C $(PARSER_DIR)

$(UTILS_OUT):
	@make -s -C $(UTILS_DIR)

clean:
	@make clean -s -C $(EXEC_DIR)
	@make clean -s -C $(PARSER_DIR)
	@make clean -s -C $(UTILS_DIR)
	@rm -f $(OBJS)

fclean: clean
	@make fclean -s -C $(EXEC_DIR)
	@make fclean -s -C $(PARSER_DIR)
	@make fclean -s -C $(UTILS_DIR)
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
