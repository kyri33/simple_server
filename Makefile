NAME = simple_server

SRC = src/server.c

FLAGS = gcc -Werror -Wextra -Wall -I includes -o

all: $(NAME)

$(NAME):
	$(FLAGS) $(NAME) $(SRC)

clean:
	rm -f $(NAME)

re: clean all
