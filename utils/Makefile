NOM = libutils.a
SRC = ft_split.c utils.c utils2.c ft_itoa.c ft_atoi.c utils3.c free_data.c
OBJ = $(SRC:.c=.o)

CC = gcc
CFLAGS = -Wall -Wextra -Werror -I..
AR = ar

all: $(NOM)

$(NOM): $(OBJ)
	$(AR) -rcs $(NOM) $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	$(RM) $(OBJ) *~

fclean: clean
	$(RM) $(NOM)

re: fclean all

.PHONY: all clean fclean re
