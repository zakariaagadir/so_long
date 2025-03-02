NAME = so_long
NAME_BONUS = so_long_bonus
CC = cc
CFLAGS = -Wall -Wextra -Werror -fsanitize=address
MLX_FLAGS = -lmlx_Linux -lX11 -lXext
SRC = main.c ft_strnstr.c ft_strlen.c parcing.c \
	read_map.c lib/get_next_line/get_next_line.c \
	lib/get_next_line/get_next_line_utils.c \
	lib/libft/ft_strdup.c lib/libft/ft_itoa.c \
	load.c anim.c exit_utils.c
SRCB = main_bonus.c ft_strnstr_bonus.c ft_strlen_bonus.c parcing_bonus.c \
	read_map_bonus.c lib/get_next_line/get_next_line.c \
	lib/get_next_line/get_next_line_utils.c \
	lib/libft/ft_strdup.c lib/libft/ft_itoa.c 
OBJ = $(SRC:.c=.o)
OBJB = $(SRCB:.c=.o)


%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(MLX_FLAGS)


bonus: $(NAME_BONUS)

$(NAME_BONUS): $(OBJB)
	$(CC) $(CFLAGS) $(OBJB) -o $(NAME_BONUS) $(MLX_FLAGS)


clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
