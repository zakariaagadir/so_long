#ifndef SO_LONG_H
#define SO_LONG_H

#include <unistd.h>
#include <mlx.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>


typedef struct s_player
{
    int x;
    int y;
}   t_player;

typedef struct s_door
{
    int x;
    int y;
}   t_door;

typedef struct s_Unemy
{
    int x;
    int y;
}   t_Unemy;

typedef struct s_map
{
    char    **full;   // The actual map (2D array)
    int     rows;     // Number of rows in the map
    int     moves;
    int     columns;
    int     coinnumber;  // Number of columns in the map
    void    *mlx;     // MLX connection pointer
    void    *win;     // MLX window pointer

    // Textures
    void *stone_image;     // Image for walls ('1')
    void *grass_image;   // Image for walkable area ('0')
    void *player_image;   // Image for player ('P')
    void *Unemy_image;
    void *coin_image; // Image for collectible ('C')
    void *door_image;     // Image for exit ('E')

    t_player player;  // Player's position
    t_door door;
    t_Unemy Unemy;
}   t_map;


char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
void    parcing(int argc, char **argv);
size_t	ft_strlen(const char *s);
int     read_map(char **argv, t_map *map);
void    free_map(t_map *full);
void    message_error(char *message, t_map *map);
void    message_error_mlx(char *message, t_map *map);
void    message_error_parcing(char *message);
int     validate_map(char **argv, t_map *map);
char	*ft_strdup(const char *s);
char	*ft_itoa(int n);





//    get_next_line
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

char	*get_next_line(int fd);
char	*ft_strchr(char *s, int c);
char	*ft_strjoin(char *s1, char *s2);
char	*reset_res(char *reserve);
char	*read_mine(int fd);
char	*get_line(char *reserve);
void	ft_memcpy(char *s1, char *s2, size_t i);





#endif