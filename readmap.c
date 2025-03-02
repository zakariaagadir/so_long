/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readmap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmounji <zmounji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 06:17:27 by zmounji           #+#    #+#             */
/*   Updated: 2025/03/02 07:46:50 by zmounji          ###   ########.fr       */
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
				return (message_error("Error: Player cannot\
					 reach all collectibles or exit",
						map), 0);
			j++;
		}
		i++;
	}
	return (1);
}

int	check_valid_chars(t_map *map)
{
	int	i;
	int	j;

	int player_count, exit_count, collectible_count;
	i = 0;
	player_count = 0, exit_count = 0, collectible_count = 0;
	while (map->full[i])
	{
		j = 0;
		while (map->full[i][j])
		{
			if (map->full[i][j] == 'P')
				player_count++;
			else if (map->full[i][j] == 'E')
				exit_count++;
			else if (map->full[i][j] == 'C')
				collectible_count++;
			else if (map->full[i][j] != '1' && map->full[i][j] != '0'
				&& map->full[i][j] != 'U')
				return (message_error("Error: Invalid character in map", map),
					0);
			j++;
		}
		i++;
	}
	if (player_count != 1 || exit_count < 1 || collectible_count < 1)
		return (message_error("Error: Map must have 1 'P',at least 1 'E' and 1 'C'",
				map), 0);
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
