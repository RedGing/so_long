/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: femorell <femorell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 15:24:14 by femorell          #+#    #+#             */
/*   Updated: 2023/03/17 12:19:24 by femorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	game_init(t_game *game)
{
	game->mlx = mlx_init();
	game->shadow = NULL;
	game->sprites = NULL;
	game->rframe = NULL;
	game->lframe = NULL;
	game->cframe = NULL;
	game->player->img = NULL;
	game->coin = NULL;
	game->exit = NULL;
	game->floor = NULL;
}