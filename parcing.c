#include "so_long.h"

void    message_error(char *message, t_map *map)
{
    printf("Eror\n%s", message);
    free_map(map);
    exit(126);
}

void    message_error_parcing(char *message)
{
    printf("Eror\n%s", message);
    exit(126);
}

void    parcing(int argc, char **argv)
{
    size_t  i;

    if(argc != 2)
        message_error_parcing("number of arguments are not correct");
    i = ft_strlen(argv[1]);
    if(!ft_strnstr(&argv[1][i - 4], ".ber", 4))
        message_error_parcing("Map file extention is wrong (It should be .ber)");
}