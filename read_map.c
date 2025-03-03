/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmounji <zmounji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 06:17:27 by zmounji           #+#    #+#             */
/*   Updated: 2025/03/03 13:40:53 by zmounji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_mapc(t_map *map)
{
	int	i;

	i = 0;
	if (!map->full)
		return ;
	while (map->full[i])
		free(map->full[i++]);
	free(map->full);
	free(map);
}

t_map	*copy_map(t_map *map)
{
	int		i;
	t_map	*copy;

	i = 0;
	copy = malloc(1 * sizeof(t_map));
	if (!copy)
		return (0);
	copy->columns = map->columns;
	copy->rows = map->rows;
	copy->full = malloc(sizeof(char *) * (map->rows + 1));
	if (!copy->full)
		return (NULL);
	while (i < map->rows)
	{
		copy->full[i] = ft_strdup(map->full[i]);
		i++;
	}
	copy->full[i] = NULL;
	return (copy);
}

int	check_path_validity(t_map *map)
{
	t_map	*map_copy;
	int		i;

	map_copy = copy_map(map);
	i = 0;
	if (!map_copy)
		return (message_error("Error: Failed to copy map", map), 0);
	find_player(map, &map->player.x, &map->player.y);
	find_door(map, &map->door.x, &map->door.y);
	count_coin(map, &map->coinnumber);
	flood_fill(map_copy->full, map->player.x, map->player.y);
	count_unemy(map);
	map->unemy = malloc((map->nbunemy) * sizeof(t_Unemy));
	while (i < map->nbunemy)
	{
		find_unemy(map, &map->unemy[i].x, &map->unemy[i].y, i);
		i++;
	}
	if (!is_path_valid(map_copy))
		return (free_mapc(map_copy), 0);
	map->moves = 0;
	free_mapc(map_copy);
	return (1);
}

int	validate_map(char **argv, t_map *map)
{
	map->full = NULL;
	map->unemy = NULL;
	inisialisevoids(map);
	if (!read_map(argv, map))
		return (0);
	if (!check_rectangle(map))
		return (0);
	if (!check_walls(map))
		return (0);
	if (!check_valid_chars(map))
		return (0);
	if (!check_path_validity(map))
		return (0);
	return (1);
}
