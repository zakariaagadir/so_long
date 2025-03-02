/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readmaputil.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmounji <zmounji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 06:17:27 by zmounji           #+#    #+#             */
/*   Updated: 2025/03/02 08:57:30 by zmounji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	find_player(t_map *map, int *x, int *y)
{
	int	i;
	int	j;

	i = 0;
	while (map->full[i])
	{
		j = 0;
		while (map->full[i][j])
		{
			if (map->full[i][j] == 'P')
			{
				*x = j;
				*y = i;
				return ;
			}
			j++;
		}
		i++;
	}
}

void	count_unemy(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (map->full[i])
	{
		j = 0;
		while (map->full[i][j])
		{
			if (map->full[i][j] == 'U')
			{
				map->nbunemy++;
			}
			j++;
		}
		i++;
	}
}

void	find_unemy(t_map *map, int *x, int *y, int index)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	count = 0;
	while (map->full[i])
	{
		j = 0;
		while (map->full[i][j])
		{
			if (map->full[i][j] == 'U')
			{
				if (count == index)
				{
					*x = j;
					*y = i;
					return ;
				}
				count++;
			}
			j++;
		}
		i++;
	}
}

void	find_door(t_map *map, int *x, int *y)
{
	int	i;
	int	j;

	i = 0;
	if (!map || !map->full)
		return ;
	while (map->full[i])
	{
		j = 0;
		while (map->full[i][j])
		{
			if (map->full[i][j] == 'E')
			{
				*x = j;
				*y = i;
			}
			j++;
		}
		i++;
	}
}

void	flood_fill(char **map, int x, int y)
{
	if (map[y][x] == '1' || map[y][x] == 'F' /*|| map[y][x] == 'U'*/)
		return ;
	map[y][x] = 'F';
	flood_fill(map, x + 1, y);
	flood_fill(map, x - 1, y);
	flood_fill(map, x, y + 1);
	flood_fill(map, x, y - 1);
}
