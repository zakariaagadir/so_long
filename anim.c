/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anim.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmounji <zmounji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 06:17:27 by zmounji           #+#    #+#             */
/*   Updated: 2025/03/02 04:13:56 by zmounji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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
            return (message_error_mlx("You are Lose\n", map), 0);
        p++;
    }
    map->current_frame = (map->current_frame + 1) % 8;
    draw_map(map);
    mlx_put_image_to_window(map->mlx, map->win, map->player_image, map->player.x * 64, map->player.y * 64);

    return (0);
}
