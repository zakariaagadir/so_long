/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmounji <zmounji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 06:17:27 by zmounji           #+#    #+#             */
/*   Updated: 2025/03/03 13:27:49 by zmounji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <X11/X.h>
# include <X11/keysym.h>
# include <fcntl.h>
# include <mlx.h>
# include <stdio.h>
# include <stdlib.h>
# include <time.h>
# include <unistd.h>
# include <unistd.h>

# define ENEMY_SPEED 50

typedef struct s_player
{
	int			x;
	int			y;
}				t_player;

typedef struct s_door
{
	int			x;
	int			y;
}				t_door;

typedef struct s_Unemy
{
	int			x;
	int			y;
	int			tracker;
	int			direction;
}				t_Unemy;

typedef struct s_map
{
	char		**full;
	int			rows;
	int			moves;
	int			columns;
	int			coinnumber;
	void		*mlx;
	void		*win;
	void		*player_images[8];
	void		*player_images_left[8];
	int			current_frame;
	int			is_moving;

	void		*stone_image;
	void		*grass_image;
	void		*player_image;
	void		*unemy_image[10];
	void		*coin_image;
	void		*door_image;
	int			nbunemy;

	t_player	player;
	t_door		door;
	t_Unemy		*unemy;
}				t_map;

char			*ft_strnstr(const char *haystack, const char *needle,
					size_t len);
void			load_unemy(t_map *map, int w, int h, int i);
void			load_playerf(t_map *map);
int				animate_player(t_map *map);
void			load_playerl(t_map *map);
void			inisialisevoids(t_map *map);
void			unemy_mv_w(t_map *map);
void			draw_map(t_map *map);
void			load_textures(t_map *map);
int				check_rectangle(t_map *map);
int				check_walls(t_map *map);
void			count_coin(t_map *map, int *coinnumber);
void			draw_map(t_map *map);
int				closegame(t_map *map);
int				is_path_valid(t_map *map);
int				check_valid_chars(t_map *map);
void			free_map(t_map *map);
void			find_player(t_map *map, int *x, int *y);
void			count_unemy(t_map *map);
void			find_unemy(t_map *map, int *x, int *y, int index);
void			find_door(t_map *map, int *x, int *y);
void			flood_fill(char **map, int x, int y);
void			parcing(int argc, char **argv);
size_t			ft_strlen(const char *s);
int				read_map(char **argv, t_map *map);
void			free_map(t_map *full);
void			message_error(char *message, t_map *map);
void			message_error_un(char *message, t_map *map);
void			message_error_mlx(char *message, t_map *map);
void			message_error_parcing(char *message);
int				validate_map(char **argv, t_map *map);
char			*ft_strdup(const char *s);
char			*ft_itoa(int n);
void			winner(char *message, t_map *map);

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

char			*get_next_line(int fd);
char			*ft_strchr(char *s, int c);
char			*ft_strjoin(char *s1, char *s2);
char			*reset_res(char *reserve);
char			*read_mine(int fd);
char			*get_line(char *reserve);
void			ft_memcpy(char *s1, char *s2, size_t i);

#endif