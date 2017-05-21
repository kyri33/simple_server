NAME = simple_server

SRC = src/server.c  src/data.c

FLAGS = gcc -Werror -Wextra -Wall -I includes -o

all: $(NAME)

$(NAME): $(SRC)
	$(FLAGS) $(NAME) $(SRC)

clean:
	rm -f $(NAME)

re: clean all
