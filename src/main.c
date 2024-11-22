/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: femorell <femorell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 15:24:31 by femorell          #+#    #+#             */
/*   Updated: 2023/03/17 12:10:17 by femorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	exit_error(int er, char *msg, t_game *game)
{
	ft_printf("%s\n", msg);
	if (er == 1)
	{
		free(game->player);
		ft_free_matrix(game->map);
	}
	exit(1);
}

static int	game_loop(t_game *game)
{
	static int	inter;

	if (inter > 2500)
	{
		inter = 0;
		create_map(game);
	}
	inter++;
	return (1);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
		exit_error(0, "Error\nMap is missing or wrong arguments.", &game);
	game.alloc = NULL;
	game.img_alloc = NULL;
	map_read(&game, argv[1]);
	map_check(&game, argv[1]);
	game_init(&game);
	map_render(&game);
	mlx_hook(game.win, 2, 1L << 0, keydown_hook, &game);
	mlx_hook(game.win, 17, 0, kill_hook, &game);
	mlx_key_hook(game.win, keyup_hook, &game);
	mlx_loop_hook(game.mlx, game_loop, &game);
	mlx_loop(game.mlx);
	return (0);
}
