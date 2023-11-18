/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kallegre <kallegre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 05:43:38 by wilson            #+#    #+#             */
/*   Updated: 2023/11/18 14:26:06 by kallegre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	**split_map(char **map, int i, int split)
{
	char	*tmp;
	char	**param;

	while (map[++i])
	{
		if (ft_strlen(map[i]) > 1)
		{
			tmp = trim_space(ft_substr(map[i], 0, ft_strlen(map[i]) - 1));
			param = ft_split(tmp, ' ');
			if (!ft_strncmp(param[0], "NO", 3) || !ft_strncmp(param[0], "SO", 3)
				|| !ft_strncmp(param[0], "WE", 3) || !ft_strncmp(param[0], "EA", 3)
				|| !ft_strncmp(param[0], "F", 2) || !ft_strncmp(param[0], "C", 2))
				split = i;
		}
	}
	free(tmp);
	double_free(param);
	param = dupntab(map, split + 1, ft_tablen(map));
	return (param);
}

int	**convert_map(int **tab, char **map)
{
	int	i;
	int	j;

	tab = malloc(sizeof(int*) * ft_tablen(map));
	i = -1;
	while (map[++i])
	{
		j = -1;
		tab[i] = malloc(sizeof(int) * ft_strlen(map[i]));
		while (map[i][++j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'W'
					|| map[i][j] == 'E')
				map[i][j] = 0;
			else if (map[i][j] == '1' || map[i][j] == '0')
				tab[i][j] = map[i][j] - 48;
			else
				tab[i][j] = -1;
		}
	}
	return (tab);
}

void	get_player(t_game *game, char **map)
{
	int	i;
	int	j;

	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'S'
				|| map[i][j] == 'E' || map[i][j] == 'W')
			{
				game->player_pos.y = i + 0.5;
				game->player_pos.x = j + 0.5;
			}
		}
	}
}

void	check_bound(char **dup_map, int x, int y, int *out)
{
	if (!dup_map[y][x] || dup_map[y][x] == ' ' || dup_map[y][x] == '\t')
	{
		*out = 1;
		return ;
	}
	else
		dup_map[y][x] = 'Y';
	if (dup_map[y][x + 1] != '1' && dup_map[y][x + 1] != 'Y')
		check_bound(dup_map, x + 1, y, out);
	if (dup_map[y][x - 1] != '1' && dup_map[y][x - 1] != 'Y')
		check_bound(dup_map, x - 1, y, out);
	if (dup_map[y + 1][x] != '1' && dup_map[y + 1][x] != 'Y')
		check_bound(dup_map, x, y + 1, out);
	if (dup_map[y - 1][x] != '1' && dup_map[y - 1][x] != 'Y')
		check_bound(dup_map, x, y - 1, out);
}

int	check_map(t_game *game, char **map)
{
	int		i;
	int		j;
	int		out;
	char	**dup_map;

	i = 0;
	out = 0;
	dup_map = dupntab(map, 0, ft_tablen(map));
	get_player(game, map);
	check_bound(dup_map, game->player_pos.x, game->player_pos.y, &out);
	if (out == 1)
		return (0);
	if (map[(int)game->player_pos.y][(int)game->player_pos.x] == 'N')
		game->player_orientation = -M_PI / 2;
	else if (map[(int)game->player_pos.y][(int)game->player_pos.x] == 'S')
		game->player_orientation = M_PI / 2;
	else if (map[(int)game->player_pos.y][(int)game->player_pos.x] == 'E')
		game->player_orientation = M_PI;
	else if (map[(int)game->player_pos.y][(int)game->player_pos.x] == 'W')
		game->player_orientation = 0;
	// game->map = convert_map(game->map, map);
	map[(int)game->player_pos.y][(int)game->player_pos.x] = '0';
	game->map = map;
	return (1);
}
