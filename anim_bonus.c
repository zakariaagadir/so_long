/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anim_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmounji <zmounji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 06:17:27 by zmounji           #+#    #+#             */
/*   Updated: 2025/03/02 22:20:22 by zmounji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	handler_anim(t_map *map)
{
	draw_map(map);
	mlx_put_image_to_window(map->mlx, map->win, map->player_image, map->player.x
		* 64, map->player.y * 64);
}

int	animate_player(t_map *map)
{
	int	newx;
	int	p;

	p = 0;
	while (p < map->nbunemy)
	{
		map->unemy[p].tracker++;
		if (map->unemy[p].tracker > (ENEMY_SPEED * 10))
		{
			newx = map->unemy[p].x + (1 * map->unemy[p].direction);
			if (map->full[map->unemy[p].y][newx] != '1')
				map->unemy[p].x += 1 * (map->unemy[p].direction);
			else
				map->unemy[p].direction *= -1;
			map->unemy[p].tracker = 0;
		}
		if (map->player.y == map->unemy[p].y
			&& map->player.x == map->unemy[p].x)
			return (message_error_mlx("You are Lose\n", map), 0);
		p++;
	}
	map->current_frame = (map->current_frame + 1) % 8;
	handler_anim(map);
	return (0);
}
