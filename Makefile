CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c99

SRC = my_mastermind.c
OBJ = $(SRC:.c=.o)
EXECUTABLE = my_mastermind

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(EXECUTABLE)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(EXECUTABLE) $(OBJ)

fclean: clean

re: fclean all

.PHONY: all clean fclean re
