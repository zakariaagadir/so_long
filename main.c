#include "so_long.h"

void load_textures(t_map *map)
{
    int w, h;

    map->mlx = mlx_init();
    if (!map->mlx)
    {
        write(2, "Error: MLX initialization failed\n", ft_strlen("Error: MLX initialization failed\n"));
        exit(EXIT_FAILURE);
    }
    map->win = mlx_new_window(map->mlx, map->columns * 64, map->rows * 64, "My Window");

    map->stone_image = mlx_xpm_file_to_image(map->mlx, "textures/stone_wall02.xpm", &w, &h);
    map->grass_image = mlx_xpm_file_to_image(map->mlx, "textures/grass.xpm", &w, &h);
    map->player_image = mlx_xpm_file_to_image(map->mlx, "textures/player.xpm", &w, &h);
    map->coin_image = mlx_xpm_file_to_image(map->mlx, "textures/coin.xpm", &w, &h);
    map->door_image = mlx_xpm_file_to_image(map->mlx, "textures/door.xpm", &w, &h);

    if (!map->stone_image || !map->grass_image || !map->player_image || !map->coin_image || !map->door_image)
    {
        write(2, "Error: Failed to load textures\n", ft_strlen("Error: Failed to load textures\n"));
        exit(EXIT_FAILURE);
    }
}

void draw_map(t_map *map)
{
    int x, y;

    y = 0;
    while (y < map->rows)
    {
        x = 0;
        while (x < map->columns)
        {
            if (map->full[y][x] == '1')
                mlx_put_image_to_window(map->mlx, map->win, map->stone_image, x * 64, y * 64);
            else
            {
                mlx_put_image_to_window(map->mlx, map->win, map->grass_image, x * 64, y * 64);
                if (map->full[y][x] == 'C')
                    mlx_put_image_to_window(map->mlx, map->win, map->coin_image, x * 64, y * 64);
                else if (map->full[y][x] == 'E')
                    mlx_put_image_to_window(map->mlx, map->win, map->door_image, x * 64, y * 64);
            }
            x++;
        }
        y++;
    }
    // Draw player separately to avoid flickering
    mlx_put_image_to_window(map->mlx, map->win, map->player_image, map->player.x * 64, map->player.y * 64);
}

int key_press(int keycode, t_map *map)
{
    if (keycode == 65307) // Escape key
    {
        free_map(map);
        exit(0);
    }

    int new_x = map->player.x;
    int new_y = map->player.y;

    if (keycode == 65361 && map->full[map->player.y][map->player.x - 1] != '1') // Left
        new_x--;
    if (keycode == 65363 && map->full[map->player.y][map->player.x + 1] != '1') // Right
        new_x++;
    if (keycode == 65362 && map->full[map->player.y - 1][map->player.x] != '1') // Up
        new_y--;
    if (keycode == 65364 && map->full[map->player.y + 1][map->player.x] != '1') // Down
        new_y++;

    if (map->full[new_y][new_x] != '1') // Move only if not a wall
    {
        map->player.x = new_x;
        map->player.y = new_y;
        if(map->full[map->player.y][map->player.x] == 'C')
        {
            map->full[map->player.y][map->player.x] = '0';
            map->coinnumber--;

        }
        else if(map->full[map->player.y][map->player.x] == 'E')
                return (message_error("finished\n", map), 0);
        else if(map->coinnumber == 0)
            map->full[map->door.y][map->door.x] = 'E';
        draw_map(map); // Redraw the player only
    }
    return (0);
}

int main(int argc, char **argv)
{
    t_map *map;

    parcing(argc, argv);
    map = malloc(sizeof(t_map));
    if (!map)
        return (1);

    if (validate_map(argv, map))
    {
        load_textures(map);
        map->full[map->door.y][map->door.x] = '0';
        draw_map(map);

        mlx_hook(map->win, 2, 1L << 0, key_press, map); // Handle key press events
        mlx_loop(map->mlx);
    }

    free_map(map);
    return (0);
}
