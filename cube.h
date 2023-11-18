/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kallegre <kallegre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 15:32:19 by kallegre          #+#    #+#             */
/*   Updated: 2023/11/18 14:08:40 by kallegre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_H
#define CUBE_H

# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include "mlx_linux/mlx.h"

# define KEY_ESC 65307
# define KEY_W 119
# define KEY_S 115
# define KEY_A 97
# define KEY_D 100
# define KEY_LEFT 65361
# define KEY_RIGHT 65363

# define M_PI	3.14159265358979323846

typedef struct 
{
	double x;
	double y;
} vect;


typedef struct s_image 
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}		t_image;

typedef struct s_data 
{
	void	*mlx;
	void	*win;
	char	**map;
	t_image	texture;
	int		texture_width;
	int		texture_height;
	t_image	map_img;
	t_image	player_img;
	t_image ray_colision;
	vect	player_pos;
	double	player_orientation;
}		t_data;

void	my_mlx_pixel_put(t_image *image, int x, int y, int color);
void	add_wall(t_image *map, int x, int y);
t_image	create_map_img(t_data data);
t_image	create_player_img(t_data data);

int		key_pressed(int key, t_data *data);
int		render_game(t_data *data);
int		close_win(t_data *data);

void	ray_casting(t_data data);


#endif