#include "so_long.h"

void    message_error(char *message)
{
    printf("Eror\n%s", message);
    exit(126);
}

void    parcing(int argc, char **argv)
{
    size_t  i;

    if(argc != 2)
        message_error("number of arguments are not correct");
    i = ft_strlen(argv[1]);
    if(!ft_strnstr(&argv[1][i - 4], ".ber", 4))
        message_error("Map file extention is wrong (It should be .ber)");
}