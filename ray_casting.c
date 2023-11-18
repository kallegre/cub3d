/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kallegre <kallegre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 00:05:50 by kallegre          #+#    #+#             */
/*   Updated: 2023/11/18 13:55:02 by kallegre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// int	main()
// {
// 	t_data	data;
// 	data.mlx = mlx_init();
// 	data.win = mlx_new_window(data.mlx, 1000, 600, "cub3d");

// 	data.texture.img = mlx_xpm_file_to_image(data.mlx, "texture.xpm", &data.texture_width, &data.texture_height);
// 	data.texture.addr = mlx_get_data_addr(data.texture.img, 
// 		&data.texture.bits_per_pixel, &data.texture.line_length, &data.texture.endian);

// 	data.map = (int **)malloc(10 * sizeof(int *));
// 	int i = 0;
// 	int j = 0;
// 	while (i < 10)
// 	{
// 		data.map[i] = (int *)malloc(10 * sizeof(int));
// 		j = 0;
// 		while (j < 10)
// 		{
// 			if (j == 0 || j == 9 || i == 0 || i == 9)
// 			{
// 				data.map[i][j] = 1;
// 				j++;
// 				continue;
// 			}
// 			data.map[i][j] = 0;
// 			j++;
// 		}
// 		i++;
// 	}
// 	data.map[1][3] = 1;
// 	data.map[2][3] = 1;
// 	data.map[3][3] = 1;

// 	data.player_pos.x = 2;
// 	data.player_pos.y = 2;

// 	data.player_orientation = -M_PI/2;

// 	data.map_img = create_map_img(data);
// 	data.player_img = create_player_img(data);

// 	ray_casting(data);
// 	mlx_put_image_to_window(data.mlx, data.win, data.map_img.img, 10, 10);
// 	mlx_put_image_to_window(data.mlx, data.win, data.player_img.img, data.player_pos.x * 10 + 9, data.player_pos.y * 10 + 9);

// 	mlx_hook(data.win, 2, 1L << 0, &key_pressed, &data);
// 	// mlx_key_hook(data.win, &key_pressed, &data);
// 	mlx_hook(data.win, 17, (1L << 17), &close_win, &data);
// 	mlx_loop(data.mlx);
// 	return (0);
// }

void	display_line(t_game data, int x, double distance, vect hyp_scale)
{
	int	h;
	int	i;

	if (distance == 0)
	{
		printf("distance == 0");
		return ;
	}

	if (distance > 10)
	{
		i = 0;
		while (i < 300)
		{
			my_mlx_pixel_put(&data.ray_colision, x, 300 + i, 0x403C3B);
			my_mlx_pixel_put(&data.ray_colision, x, 300 - i, 0x1e3d59);
			i++;
		}
		return ;
	}

	h = 500/distance;

	i = 0;
	while (i < h/2 && i < 300)
	{
		my_mlx_pixel_put(&data.ray_colision, x, 300 + i, 0x242221);
		my_mlx_pixel_put(&data.ray_colision, x, 300 - i, 0x242221);
		i++;
	}
	while (i < 300)
	{
		my_mlx_pixel_put(&data.ray_colision, x, 300 + i, 0x403C3B);
		my_mlx_pixel_put(&data.ray_colision, x, 300 - i, 0x1e3d59);
		i++;
	}
}

void	ray_casting(t_game data)
{
	data.ray_colision.img = mlx_new_image(data.mlx, 1000, 600);
	data.ray_colision.addr = mlx_get_data_addr(data.ray_colision.img, 
		&data.ray_colision.bits_per_pixel, &data.ray_colision.line_length, &data.ray_colision.endian);

	vect	end;
	vect	hyp_scale;
	vect	ray_dir;
	vect	ray_len;
	vect	tile_pos;
	double	distance = 0;

	int		i = 0;
	double	rota = -M_PI/4;

	while (rota <= M_PI/4)
	{
		tile_pos.x = (int)data.player_pos.x;
		tile_pos.y = (int)data.player_pos.y;

		end.x = cos(data.player_orientation + rota);
		end.y = sin(data.player_orientation + rota);

		hyp_scale.x = sqrt(1 + pow(end.y / end.x, 2));
		hyp_scale.y = sqrt(1 + pow(end.x / end.y, 2));

		if (end.x > 0)
		{
			ray_dir.x = 1;
			ray_len.x = (tile_pos.x + 1 - data.player_pos.x) * hyp_scale.x;
		}
		else
		{
			ray_dir.x = -1;
			ray_len.x = (data.player_pos.x - tile_pos.x) * hyp_scale.x;
		}
		if (end.y > 0)
		{
			ray_dir.y = 1;
			ray_len.y = (tile_pos.y + 1 - data.player_pos.y) * hyp_scale.y;
		}
		else
		{
			ray_dir.y = -1;
			ray_len.y = (data.player_pos.y - tile_pos.y) * hyp_scale.y;
		}

		while (distance <= 1000)
		{
			if (ray_len.x < ray_len.y)
			{
				tile_pos.x += ray_dir.x;
				distance = ray_len.x;
				if (data.map[(int)tile_pos.y][(int)tile_pos.x] != '0')
					break ;
				ray_len.x += hyp_scale.x;
			}
			else
			{
				tile_pos.y += ray_dir.y;
				distance = ray_len.y;
				if (data.map[(int)tile_pos.y][(int)tile_pos.x] != '0')
					break ;
				ray_len.y += hyp_scale.y;
			}
		}
		if (distance == ray_len.x)
			display_line(data, i, distance, hyp_scale);
		else
			display_line(data, i, distance, hyp_scale);
		i++;
		rota += M_PI/2000;
	}

	mlx_put_image_to_window(data.mlx, data.win, data.ray_colision.img, 0, 0);
	mlx_destroy_image(data.mlx, data.ray_colision.img);
}
