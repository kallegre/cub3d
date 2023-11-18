/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kallegre <kallegre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 00:08:53 by kallegre          #+#    #+#             */
/*   Updated: 2023/11/18 14:23:16 by kallegre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_pressed(int key, t_game *data)
{
	printf("%d\n", key);
	if (key == KEY_ESC)
		close_win(data);
	if (key == KEY_S && data->map[(int)(data->player_pos.y + 0.11)][(int)(data->player_pos.x)] == '0')
		data->player_pos.y += 0.1;
	if (key == KEY_W && data->map[(int)(data->player_pos.y - 0.11)][(int)(data->player_pos.x)] == '0')
		data->player_pos.y -= 0.1;
	if (key == KEY_D && data->map[(int)(data->player_pos.y)][(int)(data->player_pos.x + 0.11)] == '0')
		data->player_pos.x += 0.1;
	if (key == KEY_A && data->map[(int)(data->player_pos.y)][(int)(data->player_pos.x - 0.11)] == '0')
		data->player_pos.x -= 0.1;
	if (key == KEY_LEFT)
		data->player_orientation = (data->player_orientation - M_PI/8);
	if (key == KEY_RIGHT)
		data->player_orientation = (data->player_orientation + M_PI/8);
	render_game(data);
	return (0);
}

int	render_game(t_game *data)
{
	mlx_clear_window(data->mlx, data->win);
	ray_casting(*data);
	// mlx_put_image_to_window(data->mlx, data->win, data->map_img.img, 10, 10);
	// mlx_put_image_to_window(data->mlx, data->win, data->player_img.img, data->player_pos.x * 10 + 9, data->player_pos.y * 10 + 9);
	return (0);
}

int	close_win(t_game *data)
{
	mlx_destroy_image(data->mlx, data->map_img.img);
	mlx_destroy_image(data->mlx, data->player_img.img);
	mlx_destroy_window(data->mlx, data->win);
	exit(0);
}
