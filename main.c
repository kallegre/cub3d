/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kallegre <kallegre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 10:09:38 by wilson            #+#    #+#             */
/*   Updated: 2023/11/18 14:22:03 by kallegre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int ac, char **av)
{
	t_game	game;

	if (ac != 2)
		return (error_msg("Wrong number of arguments\n", NULL));
	if (!parsing(&game, av[1]))
		return (0);
	int	i, j;
	i = -1;
	while (game.map[++i])
	{
		j = -1;
		printf("y = %d, ", i);
		while (game.map[i][++j])
			printf("%c", game.map[i][j]);
		// printf("\n");
	}
	printf("\nplayer angle = %f\n", game.player_orientation);

	printf("player_pos = (%f, %f)\n", game.player_pos.x, game.player_pos.y);
	
	game.mlx = mlx_init();
	game.win = mlx_new_window(game.mlx, 1000, 600, "cub3d");

	// game.map_img = create_map_img(game);
	// game.player_img = create_player_img(game);

	render_game(&game);

	// mlx_hook(game.win, 2, 1L << 0, &key_pressed, &game);
	mlx_key_hook(game.win, &key_pressed, &game);
	mlx_hook(game.win, 17, (1L << 17), &close_win, &game);
	mlx_loop(game.mlx);

	return (0);
}