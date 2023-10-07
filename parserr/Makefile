NOM = libparser.a
SRC = free_tokens.c ft_memcpy.c ft_strchr.c lexer.c parser.c pipe_counter.c start.c env.c export.c env_utils.c export_utils.c fill.c fill_utils.c input_check.c readline.c expander.c
OBJ = $(SRC:.c=.o)

CC = gcc
CFLAGS = -Wall -Wextra -Werror -I..
all: $(NOM)

$(NOM): $(OBJ)
	$(AR) -rcs $(NOM) $(OBJ)

clean:
	$(RM) $(OBJ) *~

fclean: clean
	$(RM) $(NOM)

re: fclean all

.PHONY: all clean fclean re
