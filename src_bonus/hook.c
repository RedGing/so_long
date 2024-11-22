/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: femorell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 15:24:19 by femorell          #+#    #+#             */
/*   Updated: 2023/03/13 15:24:20 by femorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long_bonus.h"

int	kill_hook(t_game *game)
{
	free_game(game);
	exit(0);
}

int	keydown_hook(int keycode, t_game *game)
{
	player_act(keycode, game);
	return (0);
}

int	keyup_hook(int keycode, t_game *game)
{
	if (keycode != ESC)
		player_disact(keycode, game);
	else
		kill_hook(game);
	return (0);
}
