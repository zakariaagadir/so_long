/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_functions_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmounji <zmounji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 06:17:27 by zmounji           #+#    #+#             */
/*   Updated: 2025/03/02 22:19:13 by zmounji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	unemy_mv_w(t_map *map)
{
	int		y;
	char	*move_str;

	y = 0;
	move_str = ft_itoa(map->moves);
	mlx_string_put(map->mlx, map->win, 64, 32, 0xFFFFFF, "Mouvements : ");
	mlx_string_put(map->mlx, map->win, 64 * 3, 32, 0xFFFFFF, move_str);
	free(move_str);
	mlx_put_image_to_window(map->mlx, map->win, map->player_image, map->player.x
		* 64, map->player.y * 64);
	y = 0;
	while (y < map->nbunemy)
	{
		mlx_put_image_to_window(map->mlx, map->win,
			map->unemy_image[map->current_frame % 10], map->unemy[y].x * 64,
			map->unemy[y].y * 64);
		y++;
	}
}

void	draw_map(t_map *map)
{
	int	x;
	int	y;

	y = 0;
	while (y < map->rows)
	{
		x = 0;
		while (x < map->columns)
		{
			mlx_put_image_to_window(map->mlx, map->win, map->grass_image, x
				* 64, y * 64);
			if (map->full[y][x] == '1')
				mlx_put_image_to_window(map->mlx, map->win, map->stone_image, x
					* 64, y * 64);
			else if (map->full[y][x] == 'C')
				mlx_put_image_to_window(map->mlx, map->win, map->coin_image, x
					* 64, y * 64);
			else if (map->full[y][x] == 'E')
				mlx_put_image_to_window(map->mlx, map->win, map->door_image, x
					* 64, y * 64);
			x++;
		}
		y++;
	}
	unemy_mv_w(map);
}
