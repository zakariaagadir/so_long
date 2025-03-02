/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmounji <zmounji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 06:17:27 by zmounji           #+#    #+#             */
/*   Updated: 2025/03/02 04:14:34 by zmounji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void load_Unemy(t_map *map)
{
    int w, h;
    int i;

    i = 0;
    map->Unemy_image[0] = mlx_xpm_file_to_image(map->mlx, "textures/Unemy/Unemy1.xpm", &w, &h);
    map->Unemy_image[1] = mlx_xpm_file_to_image(map->mlx, "textures/Unemy/Unemy2.xpm", &w, &h);
    map->Unemy_image[2] = mlx_xpm_file_to_image(map->mlx, "textures/Unemy/Unemy3.xpm", &w, &h);
    map->Unemy_image[3] = mlx_xpm_file_to_image(map->mlx, "textures/Unemy/Unemy4.xpm", &w, &h);
    map->Unemy_image[4] = mlx_xpm_file_to_image(map->mlx, "textures/Unemy/Unemy5.xpm", &w, &h);
    map->Unemy_image[5] = mlx_xpm_file_to_image(map->mlx, "textures/Unemy/Unemy6.xpm", &w, &h);
    map->Unemy_image[6] = mlx_xpm_file_to_image(map->mlx, "textures/Unemy/Unemy7.xpm", &w, &h);
    map->Unemy_image[7] = mlx_xpm_file_to_image(map->mlx, "textures/Unemy/Unemy8.xpm", &w, &h);
    map->Unemy_image[8] = mlx_xpm_file_to_image(map->mlx, "textures/Unemy/Unemy9.xpm", &w, &h);
    map->Unemy_image[9] = mlx_xpm_file_to_image(map->mlx, "textures/Unemy/Unemy10.xpm", &w, &h);
    while(i<10)
    {
        if(!map->Unemy_image[i])
            message_error_mlx("is it any textur not exist",map);
        i++;
    }
}

void load_Playerf(t_map *map)
{
    int w, h;
    int i;

    i = 0;
    map->player_images[0] = mlx_xpm_file_to_image(map->mlx, "textures/player_move_front/player1.xpm", &w, &h);
    map->player_images[1] = mlx_xpm_file_to_image(map->mlx, "textures/player_move_front/player2.xpm", &w, &h);
    map->player_images[2] = mlx_xpm_file_to_image(map->mlx, "textures/player_move_front/player3.xpm", &w, &h);
    map->player_images[3] = mlx_xpm_file_to_image(map->mlx, "textures/player_move_front/player4.xpm", &w, &h);
    map->player_images[4] = mlx_xpm_file_to_image(map->mlx, "textures/player_move_front/player5.xpm", &w, &h);
    map->player_images[5] = mlx_xpm_file_to_image(map->mlx, "textures/player_move_front/player6.xpm", &w, &h);
    map->player_images[6] = mlx_xpm_file_to_image(map->mlx, "textures/player_move_front/player7.xpm", &w, &h);
    map->player_images[7] = mlx_xpm_file_to_image(map->mlx, "textures/player_move_front/player8.xpm", &w, &h);
    while(i<8)
    {
        if(!map->player_images[i])
            message_error_mlx("is it any textur not exist",map);
        i++;
    }
}

void load_Playerl(t_map *map)
{
    int w, h;
    int i;

    i = 0;
    map->player_images_left[0] = mlx_xpm_file_to_image(map->mlx, "textures/move_player_back/player1.xpm", &w, &h);
    map->player_images_left[1] = mlx_xpm_file_to_image(map->mlx, "textures/move_player_back/player2.xpm", &w, &h);
    map->player_images_left[2] = mlx_xpm_file_to_image(map->mlx, "textures/move_player_back/player3.xpm", &w, &h);
    map->player_images_left[3] = mlx_xpm_file_to_image(map->mlx, "textures/move_player_back/player4.xpm", &w, &h);
    map->player_images_left[4] = mlx_xpm_file_to_image(map->mlx, "textures/move_player_back/player5.xpm", &w, &h);
    map->player_images_left[5] = mlx_xpm_file_to_image(map->mlx, "textures/move_player_back/player6.xpm", &w, &h);
    map->player_images_left[6] = mlx_xpm_file_to_image(map->mlx, "textures/move_player_back/player7.xpm", &w, &h);
    map->player_images_left[7] = mlx_xpm_file_to_image(map->mlx, "textures/move_player_back/player8.xpm", &w, &h);
    while(i<8)
    {
        if(!map->player_images_left[i])
            message_error_mlx("is it any textur not exist",map);
        i++;
    }
}

void    inisialisevoids(t_map *map)
{
    int i;
    
    i = 0;
    while (i < 8)
    {
        map->player_images[i]=(void *)NULL;
        map->player_images_left[i]=(void *)NULL;
        map->Unemy_image[i]=(void *)NULL;
        i++;
    }
    map->Unemy_image[8]=(void *)NULL;
    map->Unemy_image[9]=(void *)NULL;
    map->stone_image=(void *)NULL;
    map->grass_image=(void *)NULL;
    map->coin_image=(void *)NULL;
    map->door_image=(void *)NULL;
}

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
    inisialisevoids(map);
    map->stone_image = mlx_xpm_file_to_image(map->mlx, "textures/stone_wall02.xpm", &w, &h);
    map->grass_image = mlx_xpm_file_to_image(map->mlx, "textures/grass.xpm", &w, &h);
    load_Unemy(map);
    load_Playerf(map);
    load_Playerl(map);
    map->player_image = map->player_images[0];
    map->current_frame = 0;
    map->is_moving = 0;
    map->coin_image = mlx_xpm_file_to_image(map->mlx, "textures/coin.xpm", &w, &h);
    map->door_image = mlx_xpm_file_to_image(map->mlx, "textures/door.xpm", &w, &h);
    if(!map->door_image || !map->coin_image || !map->grass_image || !map->stone_image)
        message_error_mlx("is it any textur not exist",map);

}
