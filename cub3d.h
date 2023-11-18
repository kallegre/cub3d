/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kallegre <kallegre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 10:10:38 by wilson            #+#    #+#             */
/*   Updated: 2023/11/18 14:08:40 by kallegre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

# define KEY_ESC 65307
# define KEY_W 119
# define KEY_S 115
# define KEY_A 97
# define KEY_D 100
# define KEY_LEFT 65361
# define KEY_RIGHT 65363

# include <stdio.h>
# include <fcntl.h>
# include <errno.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include "libft/libft.h"

# include <math.h>
# include "mlx_linux/mlx.h"

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

typedef struct s_game
{
	char    **map;
	double	player_orientation;
	vect	player_pos;
	int		split_map;
	int     t_color[3];
	int     f_color[3];
	char    *no_sprite;
	char    *so_sprite;
	char    *we_sprite;
	char    *ea_sprite;

	void	*mlx;
	void	*win;
	t_image	texture;
	int		texture_width;
	int		texture_height;
	t_image	map_img;
	t_image	player_img;
	t_image ray_colision;
}           t_game;

int		main(int ac, char **av);
int		parsing(t_game *game, char *map);
int		title(char *map, char *type);
int		error_msg(char *str, char **map);
int		get_gnlen(char *file);
char	**get_file(char **map, char *file, int start);
char	*get_next_line(int fd);
int		is_player(t_game *game, char **map);
void	get_player(t_game *game, char **map);
int		get_colors(t_game *game, char **map);
int		check_colors(char **rgb);
void	fill_colors(t_game *game, char **rgb, int check, char c);
int		get_sprite(t_game *game, char **map);
void	double_free(char **str);
char	*trim_space(char *str);
int		check_map(t_game *game, char **map);
void	check_bound(char **dup_map, int x, int y, int *out);
int		**convert_map(int **tab, char **map);
int		ft_tablen(char **tab);
char	**split_map(char **map, int i, int split);
char	**dupntab(char **tab, int start, int len);



void	my_mlx_pixel_put(t_image *image, int x, int y, int color);
void	add_wall(t_image *map, int x, int y);
t_image	create_map_img(t_game data);
t_image	create_player_img(t_game data);

int		key_pressed(int key, t_game *data);
int		render_game(t_game *data);
int		close_win(t_game *data);

void	ray_casting(t_game data);

#endif