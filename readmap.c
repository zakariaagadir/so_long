/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readmap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmounji <zmounji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 06:17:27 by zmounji           #+#    #+#             */
/*   Updated: 2025/03/02 23:03:21 by zmounji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	is_path_valid(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (map->full[i])
	{
		j = 0;
		while (map->full[i][j])
		{
			if (map->full[i][j] == 'C' || map->full[i][j] == 'E')
				return (message_error("Error: Player cannot reach \
all collectibles or exit", map), 0);
			j++;
		}
		i++;
	}
	return (1);
}

void	check_v(t_map *map, int *player_count, \
	int *exit_count, int *col_un)
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
				(*player_count)++;
			else if (map->full[i][j] == 'E')
				(*exit_count)++;
			else if (map->full[i][j] == 'C')
				col_un[0]++;
			else if (map->full[i][j] != '1' && map->full[i][j] != '0')
				message_error("Error: Invalid character in map", map);
			j++;
		}
		i++;
	}
}

int	check_valid_chars(t_map *map)
{
	int	player_count;
	int	exit_count;
	int	col_un[2];

	player_count = 0;
	exit_count = 0;
	col_un[0] = 0;
	col_un[1] = 0;
	check_v(map, &player_count, &exit_count, col_un);
	if (player_count != 1 || exit_count != 1 || col_un[0] < 1)
		return (message_error("Error: Map not valid", map), 0);
	return (1);
}

void	free_map(t_map *map)
{
	int	i;

	i = 0;
	if (!map->full)
		return ;
	while (map->full[i])
		free(map->full[i++]);
	free(map->full);
	free(map->unemy);
	free(map);
}
