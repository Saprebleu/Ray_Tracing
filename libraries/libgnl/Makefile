CC = gcc
CFLAGS = -g -Wall -Wextra -Werror
NAME = libgnl.a

SOURCES = 	get_next_line.c \
			get_next_line_utils.c

INCLUDES =	get_next_line.h

OBJECTS = $(SOURCES:.c=.o)

%.o: %.c $(INCLUDES)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJECTS)
	ar rcs $(NAME) $(OBJECTS)

all: $(NAME)

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
