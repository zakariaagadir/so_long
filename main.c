#include "so_long.h"

void load_textures(t_map *map)
{
    int w, h;

    map->mlx = mlx_init();
    if (!map->mlx)
    {
        write(2, "Error: MLX initialization failed\n", 33);
        exit(EXIT_FAILURE);
    }
    map->win = mlx_new_window(map->mlx, map->columns * 64, map->rows * 64, "My Window");

    map->stone_image = mlx_xpm_file_to_image(map->mlx, "textures/stone_wall02.xpm", &w, &h);
    map->grass_image = mlx_xpm_file_to_image(map->mlx, "textures/grass.xpm", &w, &h);
    map->Unemy_image = mlx_xpm_file_to_image(map->mlx, "textures/player_move_front/player.xpm", &w, &h);
    
    // Right walk animation frames
    map->player_images[0] = mlx_xpm_file_to_image(map->mlx, "textures/player_move_front/player1.xpm", &w, &h);
    map->player_images[1] = mlx_xpm_file_to_image(map->mlx, "textures/player_move_front/player2.xpm", &w, &h);
    map->player_images[2] = mlx_xpm_file_to_image(map->mlx, "textures/player_move_front/player3.xpm", &w, &h);
    map->player_images[3] = mlx_xpm_file_to_image(map->mlx, "textures/player_move_front/player4.xpm", &w, &h);
    map->player_images[4] = mlx_xpm_file_to_image(map->mlx, "textures/player_move_front/player5.xpm", &w, &h);
    map->player_images[5] = mlx_xpm_file_to_image(map->mlx, "textures/player_move_front/player6.xpm", &w, &h);
    map->player_images[6] = mlx_xpm_file_to_image(map->mlx, "textures/player_move_front/player7.xpm", &w, &h);
    map->player_images[7] = mlx_xpm_file_to_image(map->mlx, "textures/player_move_front/player8.xpm", &w, &h);

    // Left walk animation frames (flipped)
    map->player_images_left[0] = mlx_xpm_file_to_image(map->mlx, "textures/move_player_back/player1.xpm", &w, &h);
    map->player_images_left[1] = mlx_xpm_file_to_image(map->mlx, "textures/move_player_back/player2.xpm", &w, &h);
    map->player_images_left[2] = mlx_xpm_file_to_image(map->mlx, "textures/move_player_back/player3.xpm", &w, &h);
    map->player_images_left[3] = mlx_xpm_file_to_image(map->mlx, "textures/move_player_back/player4.xpm", &w, &h);
    map->player_images_left[4] = mlx_xpm_file_to_image(map->mlx, "textures/move_player_back/player5.xpm", &w, &h);
    map->player_images_left[5] = mlx_xpm_file_to_image(map->mlx, "textures/move_player_back/player6.xpm", &w, &h);
    map->player_images_left[6] = mlx_xpm_file_to_image(map->mlx, "textures/move_player_back/player7.xpm", &w, &h);
    map->player_images_left[7] = mlx_xpm_file_to_image(map->mlx, "textures/move_player_back/player8.xpm", &w, &h);

    map->player_image = map->player_images[0]; // Default image
    map->current_frame = 0;
    map->is_moving = 0;

    map->coin_image = mlx_xpm_file_to_image(map->mlx, "textures/coin.xpm", &w, &h);
    map->door_image = mlx_xpm_file_to_image(map->mlx, "textures/door.xpm", &w, &h);
}

void draw_map(t_map *map)
{
    int x, y;
    char *move_str;

    y = 0;
    while (y < map->rows)
    {
        x = 0;
        while (x < map->columns)
        {
            mlx_put_image_to_window(map->mlx, map->win, map->grass_image, x * 64, y * 64);
            if (map->full[y][x] == '1')
                mlx_put_image_to_window(map->mlx, map->win, map->stone_image, x * 64, y * 64);
            else if (map->full[y][x] == 'C')
                mlx_put_image_to_window(map->mlx, map->win, map->coin_image, x * 64, y * 64);
            else if (map->full[y][x] == 'E')
                mlx_put_image_to_window(map->mlx, map->win, map->door_image, x * 64, y * 64);
            x++;
        }
        y++;
    }

    move_str = ft_itoa(map->moves);  // Convert move count to string
    mlx_string_put(map->mlx, map->win, 64, 32, 0xFFFFFF, "Mouvements : ");
    mlx_string_put(map->mlx, map->win, 64*3, 32, 0xFFFFFF, move_str);
    free(move_str);
    // Draw player
    mlx_put_image_to_window(map->mlx, map->win, map->player_image, map->player.x * 64, map->player.y * 64);
    y = 0;
    while (y < map->nbUnemy)
    {
        mlx_put_image_to_window(map->mlx, map->win, map->Unemy_image, map->Unemy[y].x * 64, map->Unemy[y].y * 64);
        y++;
    }
}

int key_press(int keycode, t_map *map)
{
    
    int new_x = map->player.x;
    int new_y = map->player.y;

    if (keycode == 65307) // Escape key
        return (message_error_mlx("Esc key \n", map), 0);

    if (keycode == 65361) // Left key
    {
        if (new_x >= 0 && map->full[new_y][new_x - 1] != '1') // Prevent negative index
        {
            new_x--;
            map->moves++;
            map->is_moving = 1;
            map->player_image = map->player_images_left[map->current_frame];
        }
    }
    if (keycode == 65363) // Right key
    {
        if (new_x < map->columns - 1 && map->full[new_y][new_x + 1] != '1') // Prevent out-of-bounds access
        {
            new_x++;
            map->moves++;
            map->is_moving = 1;
            map->player_image = map->player_images[map->current_frame];
        }
    }
    if (keycode == 65362 && map->full[map->player.y - 1][map->player.x] != '1') // Up
        new_y--, map->moves++;
    if (keycode == 65364 && map->full[map->player.y + 1][map->player.x] != '1') // Down
        new_y++, map->moves++;

    if (map->full[new_y][new_x] != '1') // Move only if not a wall
    {
            map->player.x = new_x;
            map->player.y = new_y;
            if(map->full[map->player.y][map->player.x] == 'C')
            {
                map->full[map->player.y][map->player.x] = '0';
                map->coinnumber--;

            }
            if(map->full[map->player.y][map->player.x] == 'E')
                    return (message_error_mlx("finished\n", map), 0);
            
             if(map->coinnumber == 0)
                map->full[map->door.y][map->door.x] = 'E';
    }
        map->current_frame = (map->current_frame + 1) % 8; // Update animation frame
        draw_map(map);
    return (0);
}

int animate_player(t_map *map)
{
    int newx;
    int p;

    p = 0;
    while (p < map->nbUnemy)
    {
        map->Unemy[p].tracker++;
        if(map->Unemy[p].tracker > (ENEMY_SPEED * 10))
        {
            newx = map->Unemy[p].x + (1 * map->Unemy[p].direction );
            if(map->full[map->Unemy[p].y][newx]!='1')
                map->Unemy[p].x += 1* (map->Unemy[p].direction);
            else
                map->Unemy[p].direction *= -1;

        map->Unemy[p].tracker = 0;
        }
        if(map->player.y == map->Unemy[p].y && map->player.x == map->Unemy[p].x)
                        return (message_error_mlx("finished\n", map), 0);
    }
    map->current_frame = (map->current_frame + 1) % 8;
    
    draw_map(map);
    mlx_put_image_to_window(map->mlx, map->win, map->player_image, map->player.x * 64, map->player.y * 64);

    return (0);
}

// int move_enemy(t_map *map)
// {
//     static clock_t last_move = 0;
//     clock_t now = clock();
    
//     // Move enemy only if 2 seconds have passed
//     if (((double)(now - last_move) / CLOCKS_PER_SEC) >= 2.0)
//     {
//         int new_x = map->Unemy.x + map->Unemy.direction;

//         if (new_x < 0 || new_x >= map->columns || map->full[map->Unemy.y][new_x] == '1')
//             map->Unemy.direction *= -1;  // Reverse direction
//         else
//         {
//             map->full[map->Unemy.y][map->Unemy.x] = '0';
//             map->Unemy.x = new_x;  // Move enemy
//             map->full[map->Unemy.y][map->Unemy.x] = 'U';

//         }

//         last_move = now;  // Reset timer

//         // Erase previous enemy position by drawing background
//         mlx_put_image_to_window(map->mlx, map->win, map->grass_image, map->Unemy.x * 64, map->Unemy.y * 64);

//         // Draw new enemy position
//         mlx_put_image_to_window(map->mlx, map->win, map->Unemy_image, map->Unemy.x * 64, map->Unemy.y * 64);
//     }
    
//     return (0);
// }


int main(int argc, char **argv)
{
    t_map *map;
    int p;

    p = 0;
    parcing(argc, argv);
    map = malloc(sizeof(t_map));
    if (!map)
        return (1);

    if (validate_map(argv, map))
    {

    while (p < map->nbUnemy)
    {
        map->Unemy[p].tracker = 0;
        map->Unemy[p].direction = 1;
        p++;
    }
        load_textures(map);
        map->full[map->door.y][map->door.x] = '0';
        draw_map(map);

        mlx_hook(map->win, 2, 1L << 0, key_press, map); // Handle key press events
        mlx_loop_hook(map->mlx, animate_player, map);
        // mlx_loop();
        // mlx_loop_hook(mlx, draw_map, NULL);
        // mlx_loop_hook(map->mlx, move_enemy, map);
        mlx_loop(map->mlx);
    }

    free_map(map);
    return (0);
}
