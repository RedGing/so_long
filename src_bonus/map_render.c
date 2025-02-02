/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_render.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: femorell <femorell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 15:24:56 by femorell          #+#    #+#             */
/*   Updated: 2023/03/17 16:39:09 by femorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long_bonus.h"

t_image	*save_sprites(int num, char *path, t_game *game)
{
	int		i;
	char	*p;
	char	*temp;
	t_image	*sprites;

	i = 0;
	sprites = ft_malloc(sizeof(t_image) * num, &game->alloc);
	if (!sprites)
		return (NULL);
	while (i < num)
	{
		temp = ft_itoa(i);
		p = ft_strjoin(path, temp);
		free(temp);
		temp = p;
		p = ft_strjoin(temp, ".xpm");
		free(temp);
		sprites[i] = generate_image(*game, p, &game->img_alloc);
		if (!sprites[i].image)
			return (NULL);
		i++;
		free(p);
	}
	return (sprites);
}

void	init_save_sprites(t_game *game)
{
	game->shadow = save_sprites(1, SHADOW_XPM, game);
	game->lframe = save_sprites(2, LFRAME_XPM, game);
	game->cframe = save_sprites(2, CFRAME_XPM, game);
	game->rframe = save_sprites(2, RFRAME_XPM, game);
	game->sprites = save_sprites(7, WALL_XPM, game);
	game->exit = save_sprites(7, EXIT_XPM, game);
	game->floor = save_sprites(1, FLOOR_XPM, game);
	game->flower = save_sprites(3, FLOWER_XPM, game);
	game->coin = save_sprites(4, COIN_XPM, game);
	game->player->img = save_sprites(34, PLAYER_XPM, game);
	game->m_img = save_sprites(50, MONSTER_XPM, game);
	game->smonster = save_sprites(50, SMONSTER_XPM, game);
	game->cloud = save_sprites(2, CLOUD_XPM, game);
}

void	init_mlx(t_game *game)
{
	if (game->mlx == NULL)
		exit_error(0, "Error\nError in mlx. Try again.", game);
	game->win = mlx_new_window(game->mlx, game->size.x * TILE_SIZE,
			game->size.y * TILE_SIZE, "so_long");
	if (game->win == NULL)
	{
		free(game->mlx);
		exit_error(0, "Error\nFailed to create the window.", game);
	}
}

void	map_check_parameter(t_game *game)
{
	t_vector	it;

	it.y = 0;
	game->player->life = 5;
	game->player->direction = RIGHT;
	game->player->hp = 20;
	while (it.y < game->size.y)
	{
		it.x = 0;
		while (it.x < game->size.x)
		{
			if (game->map[it.y][it.x] == PLAYER)
			{
				game->player->pos.x = it.x * TILE_SIZE;
				game->player->pos.y = it.y * TILE_SIZE;
			}
			if (game->map[it.y][it.x] == MONSTER)
				monster_create(game, it);
			it.x++;
		}
		it.y++;
	}
}

void	map_render(t_game *game)
{
	game->map = map_frame(game, game->map, &game->alloc);
	map_check_parameter(game);
	game->clouds = NULL;
	clouds(game);
	init_mlx(game);
	init_save_sprites(game);
}
