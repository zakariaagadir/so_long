#include "so_long.h"

int closegame(t_map *map)
{
    int i;

    i = 0;
    while (i < 8)
    {
        if (map->mlx && map->player_images && map->player_images[i])
            mlx_destroy_image(map->mlx, map->player_images[i]);
        i++;
    }
    i = 0;
    while (i < 10)
    {
        if (map->mlx && map->Unemy_image && map->Unemy_image[i])
            mlx_destroy_image(map->mlx, map->Unemy_image[i]);
        i++;
    }
    i = 0;
    while (i < 8)
    {
        if (map->mlx && map->player_images_left && map->player_images_left[i])
            mlx_destroy_image(map->mlx, map->player_images_left[i]);
        i++;
    }
    if (map->stone_image)
        mlx_destroy_image(map->mlx, map->stone_image);
    if (map->coin_image)
        mlx_destroy_image(map->mlx, map->coin_image);
    if (map->door_image)
        mlx_destroy_image(map->mlx, map->door_image);
    if (map->grass_image)
        mlx_destroy_image(map->mlx, map->grass_image);
    if (map->win)
    {
        mlx_destroy_window(map->mlx, map->win);
        mlx_destroy_display(map->mlx);
        free(map->mlx);
    }
    free_map(map);
    exit(126);
    return(0);
}

void message_error_mlx(char *message, t_map *map)
{
    int i;

    printf("%s\n", message);
    i = 0;
    while (i < 8)
    {
        if (map->mlx && map->player_images && map->player_images[i])
            mlx_destroy_image(map->mlx, map->player_images[i]);
        i++;
    }
    i = 0;
    while (i < 10)
    {
        if (map->mlx && map->Unemy_image && map->Unemy_image[i])
            mlx_destroy_image(map->mlx, map->Unemy_image[i]);
        i++;
    }
    i = 0;
    while (i < 8)
    {
        if (map->mlx && map->player_images_left && map->player_images_left[i])
            mlx_destroy_image(map->mlx, map->player_images_left[i]);
        i++;
    }
    if (map->stone_image)
        mlx_destroy_image(map->mlx, map->stone_image);
    if (map->coin_image)
        mlx_destroy_image(map->mlx, map->coin_image);
    if (map->door_image)
        mlx_destroy_image(map->mlx, map->door_image);
    if (map->grass_image)
        mlx_destroy_image(map->mlx, map->grass_image);
    if (map->win)
    {
        mlx_destroy_window(map->mlx, map->win);
        mlx_destroy_display(map->mlx);
        free(map->mlx);
    }
    free_map(map);
    
    exit(126);
}


void    message_error(char *message, t_map *map)
{
    printf("Eror  : %s\n", message);
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
