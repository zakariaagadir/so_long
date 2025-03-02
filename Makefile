NAME = so_long
NAME_BONUS = so_long_bonus
CC = cc
CFLAGS = -Wall -Wextra -Werror # -fsanitize=address
MLX_FLAGS = -lmlx_Linux -lX11 -lXext
SRC = main.c ft_strnstr.c ft_strlen.c parcing.c \
	read_map.c lib/get_next_line/get_next_line.c \
	lib/get_next_line/get_next_line_utils.c \
	lib/libft/ft_strdup.c lib/libft/ft_itoa.c \
	load.c anim.c exit_utils.c chekmap.c readmaputil.c\
	readmap.c loadutil.c main_functions.c
SRCB = anim_bonus.c load_bonus.c read_map_bonus.c\
	chekmap_bonus.c loadutil_bonus.c readmap_bonus.c\
	exit_utils_bonus.c main_bonus.c readmaputil_bonus.c\
	ft_strlen_bonus.c main_functions_bonus.c\
	ft_strnstr_bonus.c parcing_bonus.c\
	lib/get_next_line/get_next_line.c \
	lib/get_next_line/get_next_line_utils.c\
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
	rm -f $(OBJ) $(OBJB)

fclean: clean
	rm -f $(NAME) $(NAME_BONUS)

re: fclean all
