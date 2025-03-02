/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmounji <zmounji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 06:17:27 by zmounji           #+#    #+#             */
/*   Updated: 2025/03/02 04:14:46 by zmounji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	unemy_mv_w(t_map *map)
{
	int		y;
	char	*move_str;

	y = 0;
	move_str = ft_itoa(map->moves); // Convert move count to string
	mlx_string_put(map->mlx, map->win, 64, 32, 0xFFFFFF, "Mouvements : ");
	mlx_string_put(map->mlx, map->win, 64 * 3, 32, 0xFFFFFF, move_str);
	free(move_str);
	mlx_put_image_to_window(map->mlx, map->win, map->player_image, map->player.x
		* 64, map->player.y * 64);
	y = 0;
	while (y < map->nbUnemy)
	{
		mlx_put_image_to_window(map->mlx, map->win,
			map->Unemy_image[map->current_frame % 10], map->Unemy[y].x * 64,
			map->Unemy[y].y * 64);
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

int	handl_fun(t_map *map, int *new_y, int *new_x)
{
	if (map->full[*new_y][*new_x] != '1')
	{
		map->player.x = *new_x;
		map->player.y = *new_y;
		if (map->full[map->player.y][map->player.x] == 'C')
		{
			map->full[map->player.y][map->player.x] = '0';
			map->coinnumber--;
		}
		if (map->full[map->player.y][map->player.x] == 'E')
			return (winner("you are win\n", map), 0);
		if (map->coinnumber == 0)
			map->full[map->door.y][map->door.x] = 'E';
	}
	map->current_frame = (map->current_frame + 1) % 8;
	draw_map(map);
	return (0);
}

int	key_press(int keycode, t_map *map)
{
	int	new_x;
	int	new_y;

	new_x = map->player.x;
	new_y = map->player.y;
	if (keycode == 65307 || keycode == 42)
		return (message_error_mlx("Esc key \n", map), 0);
	if (keycode == 65361)
		if (new_x >= 0 && map->full[new_y][new_x - 1] != '1')
		{
			new_x--;
			map->moves++;
			map->is_moving = 1;
			map->player_image = map->player_images_left[map->current_frame];
		}
	if (keycode == 65363)
		if (new_x < map->columns - 1 && map->full[new_y][new_x + 1] != '1')
		{
			new_x++;
			map->moves++;
			map->is_moving = 1;
			map->player_image = map->player_images[map->current_frame];
		}
	if (keycode == 65362 && map->full[map->player.y - 1][map->player.x] != '1')
		new_y--, map->moves++;
	if (keycode == 65364 && map->full[map->player.y + 1][map->player.x] != '1')
		new_y++, map->moves++;
	return (handl_fun(map, &new_y, &new_x));
}

int	main(int argc, char **argv)
{
	t_map	*map;
	int		p;

	p = 0;
	parcing(argc, argv);
	map = malloc(sizeof(t_map));
	if (!map)
		return (1);
	map->nbUnemy = 0;
	if (validate_map(argv, map))
	{
		while (p < map->nbUnemy)
		{
			map->Unemy[p].tracker = 0;
			map->Unemy[p++].direction = 1;
		}
		load_textures(map);
		map->full[map->door.y][map->door.x] = '0';
		draw_map(map);
		mlx_hook(map->win, 2, 1L << 0, key_press, map);
			// Handle key press events
		mlx_loop_hook(map->mlx, animate_player, map);
		mlx_hook(map->win, 17, 0, closegame, map);
		mlx_loop(map->mlx);
	}
	return (free_map(map), 0);
}
