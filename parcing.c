/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmounji <zmounji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 06:17:27 by zmounji           #+#    #+#             */
/*   Updated: 2025/03/03 01:16:00 by zmounji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	message_error(char *message, t_map *map)
{
	write(2, message, ft_strlen(message));
	if (map && map->full && map->full[0])
		write(2, map->full[0], 1);
	write(2, "\n", 1);
}

void	message_error_parcing(char *message)
{
	printf("Eror\n%s", message);
	exit(EXIT_FAILURE);
}

void	parcing(int argc, char **argv)
{
	size_t	i;

	if (argc != 2)
		message_error_parcing("number of arguments are not correct");
	i = ft_strlen(argv[1]);
	if (!ft_strnstr(&argv[1][i - 4], ".ber", 4))
		message_error_parcing("Map file extention is\
		wrong (It should be .ber)");
}
