NAME = cub3D
CC = cc
FLAGS = -Wall -Wextra -Werror
HEADER = includes/cub3d.h
SRC = src/main.c
OBJECTS = $(SRC:src/%.c=obj/%.o)
LINKS = -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz
INCLUDES = -Iincludes -I/usr/include -Imlx_linux

all: $(NAME)

$(NAME): $(OBJECTS)
		$(CC) $(FLAGS) $(OBJECTS) $(LINKS) -o $(NAME)
		
obj/%.o: src/%.c $(HEADER)
		mkdir -p $(dir $@)
		$(CC) $(FLAGS) $(INCLUDES) -c $< -o $@

clean:
		rm -rf $(OBJECTS)

fclean: clean
		rm -f $(NAME)
		
re: fclean all

.PHONY: all clean fclean re