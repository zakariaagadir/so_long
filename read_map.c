/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmounji <zmounji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 06:17:27 by zmounji           #+#    #+#             */
/*   Updated: 2025/03/02 04:15:06 by zmounji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int read_map(char **argv, t_map *map)
{
    int     fd;
    char    *line;
    int     i = 0;

    fd = open(argv[1], O_RDONLY);
    if (fd == -1)
        return (message_error("Error: permission denied", map), 0);

    map->rows = 0;
    while ((line = get_next_line(fd)))
    {
        free(line);
        line = NULL;
        map->rows++;
    }
    close(fd);

    map->full = malloc(sizeof(char *) * (map->rows + 1));
    if (!map->full)
        return (message_error("Error: Memory allocation failed", map), 0);

    fd = open(argv[1], O_RDONLY);
    while ((line = get_next_line(fd)))
    {
        map->full[i] = line;
        map->columns = ft_strlen(map->full[i++]);
    }
    map->full[i] = NULL;
    close(fd);
    return (1);
}

int check_rectangle(t_map *map)
{
    int width = ft_strlen(map->full[0]);
    int i = 0;

    while (map->full[i])
    {
        if ((int)ft_strlen(map->full[i]) != width)
            return (message_error("Error: Map is not rectangular", map), 0);
        i++;
    }
    map->rows = i;
    return (1);
}

int check_walls(t_map *map)
{
    int i = 0;
    int width = ft_strlen(map->full[0]);
    int height = map->rows;

    // Check first and last row
    while (i < width)
    {
        if (map->full[0][i] != '1' || map->full[height - 1][i] != '1')
            return (message_error("Error: Map is not surrounded by walls",map), 0);
        i++;
    }

    i = 0;
    while (i < height)
    {
        if (map->full[i][0] != '1' || map->full[i][width - 1] != '1')
            return (message_error("Error: Map is not surrounded by walls",map), 0);
        i++;
    }
    return (1);
}

void count_coin(t_map *map, int *coinnumber)
{
    int i;
    int j;

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

void find_player(t_map *map, int *x, int *y)
{
    int i = 0, j;

    while (map->full[i])
    {
        j = 0;
        while (map->full[i][j])
        {
            if (map->full[i][j] == 'P')
            {
                *x = j;
                *y = i;
                return;
            }
            j++;
        }
        i++;
    }
}

void count_Unemy(t_map *map)
{
    int i = 0, j;

    while (map->full[i])
    {
        j = 0;
        while (map->full[i][j])
        {
            if (map->full[i][j] == 'U')
            {
                map->nbUnemy++;
            }
            j++;
        }
        i++;
    }
}

void find_Unemy(t_map *map, int *x, int *y, int index)
{
    int i = 0;
    int j;
    int count = 0; // Track how many enemies we've found

    while (map->full[i])
    {
        j = 0;
        while (map->full[i][j])
        {
            if (map->full[i][j] == 'U')
            {
                if (count == index) // Return the enemy at the given index
                {
                    *x = j;
                    *y = i;
                    return;
                }
                count++; // Found one enemy, move to the next
            }
            j++;
        }
        i++;
    }
}


void find_door(t_map *map, int *x, int *y)
{
    int i = 0, j;
    if(!map || !map->full)
        return;
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

void flood_fill(char **map, int x, int y)
{
    if (map[y][x] == '1' || map[y][x] == 'F') // '1' = Wall, 'F' = Already visited
        return;

    map[y][x] = 'F'; // Mark as visited

    flood_fill(map, x + 1, y);
    flood_fill(map, x - 1, y);
    flood_fill(map, x, y + 1);
    flood_fill(map, x, y - 1);
}

int is_path_valid(t_map *map)
{
    int i = 0, j;

    while (map->full[i])
    {
        j = 0;
        while (map->full[i][j])
        {
            if (map->full[i][j] == 'C' || map->full[i][j] == 'E') // If 'C' or 'E' still exists, return error
                return (message_error("Error: Player cannot reach all collectibles or exit", map), 0);
            j++;
        }
        i++;
    }
    return (1);
}

int check_valid_chars(t_map *map)
{
    int i = 0, j;
    int player_count = 0, exit_count = 0, collectible_count = 0;

    while (map->full[i])
    {
        j = 0;
        while (map->full[i][j])
        {
            if (map->full[i][j] == 'P') player_count++;
            else if (map->full[i][j] == 'E') exit_count++;
            else if (map->full[i][j] == 'C') collectible_count++;
            else if (map->full[i][j] != '1' && map->full[i][j] != '0' && map->full[i][j] != 'U')
                return (message_error("Error: Invalid character in map", map), 0);
            j++;
        }
        i++;
    }
    if (player_count != 1 || exit_count < 1 || collectible_count < 1)
        return (message_error("Error: Map must have 1 'P', at least 1 'E' and 1 'C'", map), 0);
    return (1);
}

void free_map(t_map *map)
{
    int i = 0;
    if(!map->full)
        return;
    while (map->full[i])
        free(map->full[i++]);
    free(map->full);
    free(map->Unemy);
    free(map);
}

void free_mapc(t_map *map)
{
    int i = 0;
    if(!map->full)
        return;
    while (map->full[i])
        free(map->full[i++]);
    free(map->full);
    free(map);
}

t_map   *copy_map(t_map *map)
{
    int i = 0;
    t_map   *copy;

    copy = malloc(1 * sizeof(t_map));
    if(!copy)
        return(0);
    copy->columns = map->columns;
    copy->rows = map->rows;
    copy->full = malloc(sizeof(char *) * (map->rows + 1));
    if (!copy->full)
        return (NULL);
    while(i < map->rows)
    {
        copy->full[i] = ft_strdup(map->full[i]);
        i++;
    }
    copy->full[i] = NULL;
    return (copy);
}

int check_path_validity(t_map *map)
{
    t_map   *map_copy = copy_map(map);
    int     i;

    i = 0;
    if (!map_copy)
        return (message_error("Error: Failed to copy map",map), 0);
    find_player(map, &map->player.x, &map->player.y);
    find_door(map, &map->door.x, &map->door.y);
    count_coin(map, &map->coinnumber);
    flood_fill(map_copy->full, map->player.x, map->player.y);
    count_Unemy(map);
    map->Unemy = malloc((map->nbUnemy)* sizeof(t_Unemy));
    while(i < map->nbUnemy)
    {
        find_Unemy(map, &map->Unemy[i].x, &map->Unemy[i].y, i);
        i++;
    }
    if (!is_path_valid(map_copy))
    {
        free_mapc(map_copy);
        return (0);
    }
    map->moves=0;
    free_mapc(map_copy);
    return (1);
}

int validate_map(char **argv, t_map *map)
{
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