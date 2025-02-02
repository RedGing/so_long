/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monster_event.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: femorell <femorell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 15:25:12 by femorell          #+#    #+#             */
/*   Updated: 2023/03/17 16:25:38 by femorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long_bonus.h"

static void	monster_act(t_monster *mon, t_game *game, t_image *map)
{
	mon->move = 0;
	if (mon->damage == -4)
		game->player->hp--;
	if (game->player->life < 1)
	{	
		mlx_destroy_image(game->mlx, map->image);
		free_game(game);
		exit_error(0, "LOSS", game);
	}
	if (game->player->hp < 1)
	{	
		game->player->hp = 20;
		game->player->life--;
	}
	else if (game->player->ac[3] == 5)
	{
		game->player->hp = 20;
		if (mon->damage == -4)
			mon->damage = 15;
		mon->life = 0;
	}
}

int	monster_vs_player(t_monster *mon, t_game *game)
{
	int			i;
	t_player	*p;

	i = 0;
	p = game->player;
	if ((p->a[0] > (mon->a[0] - NB + 1) && p->a[0] < (mon->b[0] + NB))
		|| (p->b[0] > (mon->a[0] - NB + 1) && p->b[0] < (mon->b[0] + NB)))
		i++;
	if ((p->a[1] > (mon->a[1] - NB + 1) && p->a[1] < (mon->c[1] + NB))
		|| (p->c[1] > (mon->a[1] - NB + 1) && p->c[1] < (mon->c[1] + NB)))
		i++;
	if (mon->life == 1 || mon->damage > 0)
		i++;
	return (i);
}

void	monster_event(t_game *game, t_image *map)
{
	t_list		*mons;
	t_monster	*mon;
	t_player	*p;

	mons = game->monsters;
	while (mons)
	{
		mon = ((t_monster *)mons->content);
		p = game->player;
		if (monster_vs_player(mon, game) == 3 && mon->damage == -4)
		{
			if ((p->a[0] - NB + 1) > (mon->a[0] - NB + 1))
				mon->direction = RIGHT;
			else
				mon->direction = LEFT;
			monster_act(mon, game, map);
		}
		else if (mon->life > 0)
			mon->move = 1;
		mons = mons->next;
	}
}
