/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_load_top.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: femorell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 15:26:19 by femorell          #+#    #+#             */
/*   Updated: 2023/03/13 15:26:21 by femorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long_bonus.h"

void	sprite_load_top(t_game *game, t_vector it, t_image *map)
{
	char	parameter;

	parameter = game->map[it.y][it.x];
	if (parameter == WALL)
		construct_image(game->buffer, game->pos, *map, game->sprites[1]);
}

void	sprite_init_top(t_game *game, t_image *map)
{
	t_vector	it;

	it.y = 0;
	while (it.y < game->size.y)
	{
		it.x = 0;
		while (it.x < game->size.x)
		{
			game->pos.x = it.x * TILE_SIZE;
			game->pos.y = it.y * TILE_SIZE;
			sprite_load_top(game, it, map);
			it.x++;
		}
		it.y++;
	}
	cloud_load_top(game, map);
}
