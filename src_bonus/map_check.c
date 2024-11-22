/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: femorell <femorell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 15:24:41 by femorell          #+#    #+#             */
/*   Updated: 2023/03/17 15:56:00 by femorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long_bonus.h"

static int	map_check_rectangular(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->size.y)
	{
		if (ft_strlen(game->map[i]) != game->size.x)
			return (FALSE);
		i++;
	}
	return (TRUE);
}

static int	map_check_wall(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->size.y)
	{
		if (i == 0 || i == game->size.y - 1)
		{
			j = 0;
			while (j < game->size.x)
			{
				if (game->map[i][j] != WALL)
					return (FALSE);
				j++;
			}
		}
		else
		{
			if (game->map[i][0] != WALL ||
				game->map[i][game->size.x - 1] != WALL)
				return (FALSE);
		}
		i++;
	}
	return (TRUE);
}

void	map_count_parameter2(t_game *game, int i, int j)
{
	if (game->map[i][j] == COIN)
		game->c++;
	else if (game->map[i][j] == EXIT)
		game->e++;
	else if (game->map[i][j] == PLAYER)
	{
		game->p++;
		game->player->pos.x = j;
		game->player->pos.y = i;
	}
	else if (game->map[i][j] == MONSTER)
		game->m++;
	else if (game->map[i][j] != FLOOR && game->map[i][j] != WALL &&
		game->map[i][j] != FLOWER && game->map[i][j] != FLOWER2)
		exit_error(1, "Error\nInvalid Map. Contents error.", game);
}

int	map_count_parameter(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->size.y)
	{
		j = 0;
		while (j < game->size.x)
		{
			map_count_parameter2(game, i, j);
			j++;
		}
		i++;
	}
	return (0);
}

void	map_check(t_game *game, char *filename)
{
	game->temp = 0;
	game->move = 0;
	game->c = 0;
	game->e = 0;
	game->p = 0;
	game->m = 0;
	game->player = ft_calloc(sizeof(t_player), 1);
	if (map_check_rectangular(game) == FALSE)
		exit_error(1, "Error\nThe map must be rectangular.", game);
	if (map_check_wall(game) == FALSE)
		exit_error(1, "Error\nThe map must be surrounded by walls.", game);
	map_count_parameter(game);
	if (game->c == 0)
		exit_error(1, "Error\nInvalid Map. There are no coins.", game);
	else if (game->e != 1)
		exit_error(1, "Error\nInvalid Map. Exit quantity error.", game);
	else if (game->p != 1)
		exit_error(1, "Error\nInvalid Map. Player quantity error.", game);
	else if (ft_pathcheck(game, filename) == TRUE)
		exit_error(1, "Error\nInvalid Map. Invalid Path.", game);
}
