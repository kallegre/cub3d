/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wilson <wilson@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 11:36:39 by wilson            #+#    #+#             */
/*   Updated: 2023/11/17 22:23:08 by wilson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*trim_space(char *str)
{
	char	*tmp;

	tmp = str;
	while (str && str[0])
	{
		if (str[0] == ' ' || str[ft_strlen(str)] == ' ')
			tmp = ft_strtrim(str, " ");
		else if (str[0] == '\t' || str[ft_strlen(str)] == '\t')
			tmp = ft_strtrim(str, "\t");
		else
			break ;
		free(str);
	}
	return (tmp);
}

int	get_gnlen(char *file)
{
	int		fd;
	int		i;
	char	*s;

	i = 0;
	fd = open(file, O_RDONLY);
	s = get_next_line(fd);
	while (s)
	{
		i++;
		free(s);
		s = get_next_line(fd);
	}
	if (fd == -1 || i < 3)
		return (0);
	close(fd);
	return (i);
}

int	is_player(t_game *game, char **map)
{
	int	i;
	int	j;
	int	player;

	player = 0;
	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'S'
				|| map[i][j] == 'E' || map[i][j] == 'W')
				player++;
		}
	}
	if (player != 1)
		return (0);
	return (1);
}

int	check_colors(char **rgb)
{
	int	i;
	int	j;

	if (!rgb || !rgb[2] || rgb[3] || ft_strlen(rgb[0]) > 3
		|| ft_strlen(rgb[1]) > 3 || ft_strlen(rgb[2]) > 3)
		return (0);
	j = -1;
	while (rgb[++j])
	{
		i = -1;
		while (rgb[j][++i])
		{
			if (!ft_isdigit(rgb[j][i]))
				return (0);
		}
		if (ft_atoi(rgb[j]) > 255)
			return (0);
	}
	return (1);
}

void	fill_colors(t_game *game, char **rgb, int check, char c)
{
	if (check && c == 'F')
	{
		game->f_color[0] = ft_atoi(rgb[0]);
		game->f_color[1] = ft_atoi(rgb[1]);
		game->f_color[2] = ft_atoi(rgb[2]);
	}
	else if (check && c == 'C')
	{
		game->t_color[0] = ft_atoi(rgb[0]);
		game->t_color[1] = ft_atoi(rgb[1]);
		game->t_color[2] = ft_atoi(rgb[2]);
	}
}