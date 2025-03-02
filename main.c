/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmounji <zmounji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 06:17:27 by zmounji           #+#    #+#             */
/*   Updated: 2025/03/02 10:14:28 by zmounji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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
			return (winner("you win\n", map), 0);
		if (map->coinnumber == 0)
			map->full[map->door.y][map->door.x] = 'E';
	}
	map->current_frame = (map->current_frame + 1) % 8;
	draw_map(map);
	return (0);
}

void	handle_movement(t_map *map, int keycode, int *new_y, int *new_x)
{
	if (keycode == 65361 && *new_x > 0 && map->full[*new_y][*new_x - 1] != '1')
	{
		(*new_x)--;
		map->moves++;
		map->is_moving = 1;
		map->player_image = map->player_images_left[map->current_frame];
	}
	else if (keycode == 65363 && *new_x < map->columns - 1
		&& map->full[*new_y][(*new_x)++ + 1] != '1')
	{
		map->moves++;
		map->is_moving = 1;
		map->player_image = map->player_images[map->current_frame];
	}
	else if (keycode == 65362 && *new_y > 0
		&& map->full[(*new_y)-- - 1][*new_x] != '1')
	{
		map->moves++;
	}
	else if (keycode == 65364 && *new_y < map->rows - 1
		&& map->full[*new_y + 1][*new_x] != '1')
	{
		(*new_y)++;
		map->moves++;
	}
}

int	key_press(int keycode, t_map *map)
{
	int		new_x;
	int		new_y;
	char	*move_str;

	new_x = map->player.x;
	new_y = map->player.y;
	if (keycode == 65307 || keycode == 42)
		return (message_error_mlx("Esc key \n", map), 0);
	handle_movement(map, keycode, &new_y, &new_x);
	if (keycode == 65361 || keycode == 65363
		|| keycode == 65362 || keycode == 65364)
	{
		move_str = ft_itoa(map->moves);
		write(1, "Mouvements : ", ft_strlen("Mouvements : "));
		write(1, move_str, ft_strlen(move_str));
		write(1, "\n", 1);
		free(move_str);
	}
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
	map->nbunemy = 0;
	if (validate_map(argv, map))
	{
		while (p < map->nbunemy)
		{
			map->unemy[p].tracker = 0;
			map->unemy[p++].direction = 1;
		}
		load_textures(map);
		map->full[map->door.y][map->door.x] = '0';
		draw_map(map);
		mlx_hook(map->win, 2, 1L << 0, key_press, map);
		mlx_loop_hook(map->mlx, animate_player, map);
		mlx_hook(map->win, 17, 0, closegame, map);
		mlx_loop(map->mlx);
	}
	return (free_map(map), 0);
}
