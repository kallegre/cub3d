/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wilson <wilson@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 10:32:11 by wilson            #+#    #+#             */
/*   Updated: 2023/11/18 00:08:33 by wilson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	title(char *map, char *type)
{
	int	i;
	int	j;

	i = ft_strlen(map) - 1;
	if (i < 4 || map[i - 4] == '/' || map[0] == '.' || map[0] == '/')
		return (0);
	j = 0;
	while (j < 4)
	{
		if (map[i] != type[j])
			return (0);
		j++;
		i--;
	}
	return (1);
}

char	**get_file(char **map, char *file, int start)
{
	int	fd;
	int	len;

	len = get_gnlen(file);
	fd = open(file, O_RDONLY);
	map = malloc(sizeof(char *) * (len + 1));
	if (!map)
		return (NULL);
	while (++start < len)
		map[start] = get_next_line(fd);
	map[start] = NULL;
	close(fd);
	return (map);
}

int	get_sprite(t_game *game, char **map)
{
	int		i;
	char	*tmp;
	char	**sprite;

	i = -1;
	while (map[++i])
	{
		if (ft_strlen(map[i]) > 1)
		{
			tmp = trim_space(ft_substr(map[i], 0, ft_strlen(map[i]) - 1));
			sprite = ft_split(tmp, ' ');
			if (!ft_strncmp(sprite[0], "NO", 3) && !access(sprite[1], F_OK))
				game->no_sprite = ft_strdup(sprite[1]);
			else if (!ft_strncmp(sprite[0], "SO", 3) && !access(sprite[1], F_OK))
				game->so_sprite = ft_strdup(sprite[1]);
			else if (!ft_strncmp(sprite[0], "WE", 3) && !access(sprite[1], F_OK))
				game->we_sprite = ft_strdup(sprite[1]);
			else if (!ft_strncmp(sprite[0], "EA", 3) && !access(sprite[1], F_OK))
				game->ea_sprite = ft_strdup(sprite[1]);
			double_free(sprite);
			free(tmp);
		}
	}
	if (access(game->no_sprite, F_OK) || access(game->so_sprite, F_OK)
		|| access(game->we_sprite, F_OK) || access(game->ea_sprite, F_OK))
		return (0);
	return (1);
}

int	get_colors(t_game *game, char **map)
{
	int		i;
	char	*tmp;
	char	**rgb;
	char	**colors;

	game->f_color[0] = -1;
	game->t_color[0] = -1;
	i = -1;
	while (map[++i])
	{
		if (ft_strlen(map[i]) > 1)
		{
			tmp = trim_space(ft_substr(map[i], 0, ft_strlen(map[i]) - 1));
			colors = ft_split(tmp, ' ');
			if (!ft_strncmp(colors[0], "F", 2) || !ft_strncmp(colors[0], "C", 2))
			{
				rgb = ft_split(colors[1], ',');
				if (!ft_strncmp(colors[0], "F", 2))
					fill_colors(game, rgb, check_colors(rgb), 'F');
				else if (!ft_strncmp(colors[0], "C", 2))
					fill_colors(game, rgb, check_colors(rgb), 'C');
				double_free(rgb);
			}
			double_free(colors);
			free(tmp);
		}
	}
	if (game->f_color[0] == -1 || game->t_color[0] == -1)
		return (0);
	return (1);
}

int	parsing(t_game *game, char *map)
{
	char	**temp;

	if (!title(map, "buc."))
		return (error_msg("Invalid file type\n", temp));
	temp = get_file(temp, map, -1);
	if (!temp)
		return (error_msg("Cannot initialize\n", temp));
	if (!get_sprite(game, temp))
		return (error_msg("Invalid sprits\n", temp));
	if (!title(game->no_sprite, "mpx.") || !title(game->so_sprite, "mpx.")
		|| !title(game->we_sprite, "mpx.") || !title(game->ea_sprite, "mpx."))
		return (error_msg("Invalid sprits\n", temp));
	if (!get_colors(game, temp))
		return (error_msg("Invalid colors\n", temp));
	temp = split_map(temp, -1, 0);
	if (!is_player(game, temp) || !check_map(game, temp))
		return (error_msg("Invalid map\n", temp));
	return (1);
}
