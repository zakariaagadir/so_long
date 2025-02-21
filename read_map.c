#include "so_long.h"

char    **read_map(char **argv)
{
    int     fd;
    char    *line;
    char    **map;
    int     i = 0;

    fd = open(argv[1], O_RDONLY);
    if (fd == -1)
        message_error("Error: permission denied");

    map = malloc(sizeof(char *) * 100); // Adjust size dynamically later
    if (!map)
        return (NULL);

    while ((line = get_next_line(fd)))
    {
        map[i++] = line; // Store each line in the array
    }
    map[i] = NULL; // Null-terminate the array
    close(fd);
    return (map);
}

int check_rectangle(char **map)
{
    int width = ft_strlen(map[0]); // First row length
    int i = 1;

    while (map[i])
    {
        if (ft_strlen(map[i]) != width)
            return (message_error("Error: Map is not rectangular"), 0);
        i++;
    }
    return (1);
}

int check_walls(char **map)
{
    int i = 0;
    int width = ft_strlen(map[0]);
    int height = 0;

    while (map[height])
        height++;

    // Check first and last row
    while (i < width)
    {
        if (map[0][i] != '1' || map[height - 1][i] != '1')
            return (message_error("Error: Map is not surrounded by walls"), 0);
        i++;
    }

    // Check first and last column
    for (i = 0; i < height; i++)
    {
        if (map[i][0] != '1' || map[i][width - 1] != '1')
            return (message_error("Error: Map is not surrounded by walls"), 0);
    }
    return (1);
}

void find_player(char **map, int *x, int *y)
{
    int i = 0, j;

    while (map[i])
    {
        j = 0;
        while (map[i][j])
        {
            if (map[i][j] == 'P')
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


int is_path_valid(char **map)
{
    int i = 0, j;

    while (map[i])
    {
        j = 0;
        while (map[i][j])
        {
            if (map[i][j] == 'C' || map[i][j] == 'E') // If 'C' or 'E' still exists, return error
                return (message_error("Error: Player cannot reach all collectibles or exit"), 0);
            j++;
        }
        i++;
    }
    return (1);
}


int check_valid_chars(char **map)
{
    int i = 0, j;
    int player_count = 0, exit_count = 0, collectible_count = 0;

    while (map[i])
    {
        j = 0;
        while (map[i][j])
        {
            if (map[i][j] == 'P') player_count++;
            else if (map[i][j] == 'E') exit_count++;
            else if (map[i][j] == 'C') collectible_count++;
            else if (map[i][j] != '1' && map[i][j] != '0')
                return (message_error("Error: Invalid character in map"), 0);
            j++;
        }
        i++;
    }
    if (player_count != 1 || exit_count < 1 || collectible_count < 1)
        return (message_error("Error: Map must have 1 'P', at least 1 'E' and 1 'C'"), 0);
    return (1);
}

void free_map(char **map)
{
    int i = 0;

    while (map[i])
        free(map[i++]); // Free each row
    free(map);
}


char **copy_map(char **map)
{
    int i = 0;
    char **copy;

    while (map[i]) i++; // Count number of rows

    copy = malloc(sizeof(char *) * (i + 1)); // Allocate memory for rows
    if (!copy)
        return (NULL);

    for (int j = 0; j < i; j++)
        copy[j] = ft_strdup(map[j]); // Duplicate each row

    copy[i] = NULL; // Null-terminate
    return (copy);
}


int check_path_validity(char **map)
{
    int x, y;
    char **map_copy = copy_map(map); // Make a copy of the map

    if (!map_copy)
        return (message_error("Error: Failed to copy map"), 0);

    find_player(map_copy, &x, &y); // Find player position
    flood_fill(map_copy, x, y); // Fill all reachable areas

    if (!is_path_valid(map_copy))
        return (0);

    free_map(map_copy); // Free the copied map
    return (1);
}


int validate_map(char **argv)
{
    char **map;

    map = read_map(argv);
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
