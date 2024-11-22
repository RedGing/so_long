/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: femorell <femorell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 11:55:22 by femorell          #+#    #+#             */
/*   Updated: 2023/03/17 15:53:40 by femorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long_bonus.h"

void	ft_floodfill(t_vector size, t_vector start, char **tmap)
{
	if (start.y > size.y - 1 || start.x > size.x - 1 || start.x < 0
		|| start.y < 0 || tmap[start.y][start.x] == '1')
		return ;
	tmap[start.y][start.x] = '1';
	ft_floodfill(size, (t_vector){start.x, start.y - 1}, tmap);
	ft_floodfill(size, (t_vector){start.x, start.y + 1}, tmap);
	ft_floodfill(size, (t_vector){start.x + 1, start.y}, tmap);
	ft_floodfill(size, (t_vector){start.x - 1, start.y}, tmap);
}

int	ft_pathcheck(t_game *game, char *filename)
{
	int		x;
	int		y;
	char	**tmap;

	y = 0;
	tmap = map_init(filename);
	ft_floodfill(game->size, game->player->pos, tmap);
	while (y < game->size.y)
	{
		x = 0;
		while (x < game->size.x)
		{
			if (tmap[y][x] != '1' && tmap[y][x] != '0')
			{	
				ft_free_matrix(tmap);
				return (0);
			}
			x++;
		}
		y++;
	}
	ft_free_matrix(tmap);
	return (1);
}
