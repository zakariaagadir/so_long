/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chekmap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmounji <zmounji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 06:17:27 by zmounji           #+#    #+#             */
/*   Updated: 2025/03/03 01:16:34 by zmounji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	read_handler(char **argv, t_map *map)
{
	int		fd;
	char	*line;
	int		i;

	i = 0;
	map->full = malloc(sizeof(char *) * (map->rows + 1));
	if (!map->full)
		message_error("Error: Memory allocation failed", map);
	fd = open(argv[1], O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		map->full[i] = line;
		map->columns = ft_strlen(map->full[i++]);
		line = get_next_line(fd);
	}
	map->full[i] = NULL;
	close(fd);
}

int	read_map(char **argv, t_map *map)
{
	int		fd;
	char	*line;

	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		return (message_error("Error: permission denied", map), 0);
	map->rows = 0;
	line = get_next_line(fd);
	while (line)
	{
		free(line);
		line = NULL;
		map->rows++;
		line = get_next_line(fd);
	}
	close(fd);
	read_handler(argv, map);
	return (1);
}

int	check_rectangle(t_map *map)
{
	int	width;
	int	i;

	width = ft_strlen(map->full[0]);
	i = 0;
	while (map->full[i])
	{
		if ((int)ft_strlen(map->full[i]) != width)
			return (message_error("Error: Map is not rectangular", map), 0);
		i++;
	}
	map->rows = i;
	return (1);
}

int	check_walls(t_map *map)
{
	int	i;
	int	width;
	int	height;

	i = 0;
	width = ft_strlen(map->full[0]);
	height = map->rows;
	while (i < width)
	{
		if (map->full[0][i] != '1' || map->full[height - 1][i] != '1')
			return (message_error("Error: Map is not surrounded by walls", map),
				0);
		i++;
	}
	i = 0;
	while (i < height)
	{
		if (map->full[i][0] != '1' || map->full[i][width - 1] != '1')
			return (message_error("Error: Map is not surrounded by walls", map),
				0);
		i++;
	}
	return (1);
}

void	count_coin(t_map *map, int *coinnumber)
{
	int	i;
	int	j;

	*coinnumber = 0;
	i = 0;
	while (map->full[i])
	{
		j = 0;
		while (map->full[i][j])
		{
			if (map->full[i][j] == 'C')
			{
				(*coinnumber)++;
			}
			j++;
		}
		i++;
	}
}
