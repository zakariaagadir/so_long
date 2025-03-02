/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loadutil.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmounji <zmounji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 06:17:27 by zmounji           #+#    #+#             */
/*   Updated: 2025/03/02 06:31:30 by zmounji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	load_unemy(t_map *map, int w, int h, int i)
{
	map->unemy_image[0] = mlx_xpm_file_to_image(map->mlx,
			"textures/Unemy/Unemy1.xpm", &w, &h);
	map->unemy_image[1] = mlx_xpm_file_to_image(map->mlx,
			"textures/Unemy/Unemy2.xpm", &w, &h);
	map->unemy_image[2] = mlx_xpm_file_to_image(map->mlx,
			"textures/Unemy/Unemy3.xpm", &w, &h);
	map->unemy_image[3] = mlx_xpm_file_to_image(map->mlx,
			"textures/Unemy/Unemy4.xpm", &w, &h);
	map->unemy_image[4] = mlx_xpm_file_to_image(map->mlx,
			"textures/Unemy/Unemy5.xpm", &w, &h);
	map->unemy_image[5] = mlx_xpm_file_to_image(map->mlx,
			"textures/Unemy/Unemy6.xpm", &w, &h);
	map->unemy_image[6] = mlx_xpm_file_to_image(map->mlx,
			"textures/Unemy/Unemy7.xpm", &w, &h);
	map->unemy_image[7] = mlx_xpm_file_to_image(map->mlx,
			"textures/Unemy/Unemy8.xpm", &w, &h);
	map->unemy_image[8] = mlx_xpm_file_to_image(map->mlx,
			"textures/Unemy/Unemy9.xpm", &w, &h);
	map->unemy_image[9] = mlx_xpm_file_to_image(map->mlx,
			"textures/Unemy/Unemy10.xpm", &w, &h);
	while (i < 10)
		if (!map->unemy_image[i++])
			message_error_mlx("is it any textur not exist", map);
}
