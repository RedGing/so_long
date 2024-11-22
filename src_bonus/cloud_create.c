/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cloud_create.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: femorell <femorell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 15:24:14 by femorell          #+#    #+#             */
/*   Updated: 2023/03/17 16:38:56 by femorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long_bonus.h"

void	cloud_load_top2(t_game *game, t_image *map, t_cloud *cloud)
{
	t_vector	temp;

	construct_image(game->buffer, cloud->pos, *map, game->cloud[cloud->id]);
	temp.x = cloud->pos.x;
	temp.y = cloud->pos.y + 64;
	shadow(game->buffer, temp, *map, game->cloud[cloud->id]);
}

void	cloud_load_top(t_game *game, t_image *map)
{
	t_cloud		*cloud;
	t_list		*clouds;

	clouds = game->clouds;
	while (clouds)
	{
		cloud = ((t_cloud *)clouds->content);
		if (cloud->img_inter > 1)
		{
			cloud->img_inter = 0;
			if (cloud->pos.x < -64)
			{
				cloud->pos.x = (game->size.x * 32);
				cloud->pos.y = rand() % ((game->size.y * 32) - 48 + 1) - 48;
			}
			else
				cloud->pos.x -= 1;
		}
		else
			cloud->img_inter++;
		cloud_load_top2(game, map, cloud);
		clouds = clouds->next;
	}
}

void	cloud_create(t_game *game, t_vector pos)
{
	static int	id;
	t_cloud		*cloud;

	cloud = ft_calloc(sizeof(t_cloud), 1);
	if (!cloud)
		return ;
	cloud->id = id;
	cloud->pos.x = pos.x;
	cloud->pos.y = pos.y;
	cloud->img_inter = 0;
	if (game->clouds == NULL)
		game->clouds = ft_lstnew(cloud);
	else
		ft_lstadd_front(&game->clouds, ft_lstnew(cloud));
	id++;
	if (id > 1)
		id = 0;
}

void	clouds(t_game *game)
{
	int			clouds;
	t_vector	pos;

	srand(time(NULL));
	clouds = game->size.x / 7 * game->size.y / 5;
	while (clouds)
	{
		pos.x = rand() % ((game->size.x * 32) + 1);
		pos.y = rand() % ((game->size.y * 32) - 64 + 1);
		cloud_create(game, pos);
		clouds--;
	}
}
