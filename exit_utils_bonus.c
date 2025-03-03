/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmounji <zmounji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 06:17:27 by zmounji           #+#    #+#             */
/*   Updated: 2025/03/03 13:33:45 by zmounji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	distroy_im(t_map *map, int i)
{
	while (i < 8)
	{
		if (map->mlx && map->player_images && map->player_images[i])
			mlx_destroy_image(map->mlx, map->player_images[i]);
		i++;
	}
	i = 0;
	while (i < 10)
	{
		if (map->mlx && map->unemy_image && map->unemy_image[i])
			mlx_destroy_image(map->mlx, map->unemy_image[i]);
		i++;
	}
	i = 0;
	while (i < 8)
	{
		if (map->mlx && map->player_images_left && map->player_images_left[i])
			mlx_destroy_image(map->mlx, map->player_images_left[i]);
		i++;
	}
}

int	closegame(t_map *map)
{
	int	i;

	i = 0;
	distroy_im(map, i);
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
	exit(EXIT_FAILURE);
	return (0);
}

void	winner(char *message, t_map *map)
{
	int	i;

	write(2, message, ft_strlen(message));
	write(2, "\n", 1);
	i = 0;
	distroy_im(map, i);
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
	exit(0);
}

void	message_error_mlx(char *message, t_map *map)
{
	int	i;

	write(2, message, ft_strlen(message));
	write(2, "\n", 1);
	i = 0;
	distroy_im(map, i);
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
	exit(EXIT_FAILURE);
}

void	message_error_un(char *message, t_map *map)
{
	write(2, message, ft_strlen(message));
	if (map && map->full && map->full[0])
		write(2, map->full[0], 1);
	write(2, "\n", 1);
	free_map(map);
	exit(EXIT_FAILURE);
}
