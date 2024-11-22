/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: femorell <femorell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 15:24:31 by femorell          #+#    #+#             */
/*   Updated: 2023/03/17 15:49:56 by femorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long_bonus.h"

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

long long	check_timestamp(void)
{
	struct timeval	te;
	long long		microtime;

	gettimeofday(&te, NULL);
	microtime = te.tv_sec * 1000LL + te.tv_usec / 1000;
	return (microtime);
}

static int	game_loop(t_game *game)
{
	long long	now;
	long long	diff_time;

	now = check_timestamp();
	diff_time = now - game->temp;
	if (diff_time > 15)
	{
		game->temp = now;
		create_map(game);
		player_status(game);
	}
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
