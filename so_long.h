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


char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
void    parcing(int argc, char **argv);
size_t	ft_strlen(const char *s);
char    **read_map(char **argv);
void    message_error(char *message);
int     validate_map(char **argv);
char	*ft_strdup(const char *s);



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