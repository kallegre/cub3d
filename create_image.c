/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_image.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kallegre <kallegre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 00:05:44 by kallegre          #+#    #+#             */
/*   Updated: 2023/11/18 13:45:33 by kallegre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_image *image, int x, int y, int color)
{
	char	*dst;

	dst = image->addr + (y * image->line_length + x * (image->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	add_wall(t_image *map, int x, int y)
{
	int	i = 0;
	int j = 0;
	while (i < 10)
	{
		j = 0;
		while (j < 10)
		{
			my_mlx_pixel_put(map, x + i, y + j, 0x6F6C6A);
			j++;
		}
		i++;
	}
}

t_image	create_map_img(t_game data)
{
	t_image map;

	map.img = mlx_new_image(data.mlx, 100, 100);
	map.addr = mlx_get_data_addr(map.img, 
		&map.bits_per_pixel, &map.line_length, &map.endian);

	int i = 0;
	int	j = 0;
	while (i < 10)
	{
		j = 0;
		while (j < 10)
		{
			if (data.map[j][i] == '1')
				add_wall(&map, i * 10, j * 10);
			j++;
		}
		i++;
	}
	return (map);
}

t_image	create_player_img(t_game data)
{
	t_image player;

	player.img = mlx_new_image(data.mlx, 2, 2);
	player.addr = mlx_get_data_addr(player.img, 
		&player.bits_per_pixel, &player.line_length, &player.endian);

	int	i = 0;
	int	j = 0;
	while (i < 2)
	{
		j = 0;
		while (j < 2)
		{
			my_mlx_pixel_put(&player, i, j, 0x0000FF);
			j++;
		}
		i++;
	}
	return (player);
}