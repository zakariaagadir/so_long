NAME = so_long
CC = cc
CFLAGS = -Wall -Wextra -Werror
MLX_FLAGS = -lmlx_Linux -lX11 -lXext
SRC = main.c ft_strnstr.c ft_strlen.c parcing.c \
	read_map.c lib/get_next_line/get_next_line.c \
	lib/get_next_line/get_next_line_utils.c \
	lib/libft/ft_strdup.c 
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(MLX_FLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
