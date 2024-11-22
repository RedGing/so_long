/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: femorell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 15:24:08 by femorell          #+#    #+#             */
/*   Updated: 2023/03/13 15:24:09 by femorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long_bonus.h"

void	ft_free_matrix(char **matrix)
{
	int	i;

	i = -1;
	while (matrix[++i])
		free(matrix[i]);
	free(matrix);
}

void	ft_img_clear(void *mlx_ptr, t_alloc **lst)
{
	t_alloc	*tmp;

	while (*lst)
	{
		tmp = (*lst)->next;
		mlx_destroy_image(mlx_ptr, (*lst)->ptr);
		free(*lst);
		*lst = tmp;
	}
}

void	monster_free(t_list **monsters)
{
	t_list	*tmp;

	if (*monsters)
	{
		while (*monsters != NULL)
		{
			tmp = (*monsters)->next;
			if ((*monsters)->content)
				free((*monsters)->content);
			free(*monsters);
			*monsters = tmp;
		}
	}
}

void	cloud_free(t_list **clouds)
{
	t_list	*tmp;

	if (*clouds)
	{
		while (*clouds != NULL)
		{
			tmp = (*clouds)->next;
			if ((*clouds)->content)
				free((*clouds)->content);
			free(*clouds);
			*clouds = tmp;
		}
	}
}

void	free_game(t_game *game)
{	
	ft_img_clear(game->mlx, &game->img_alloc);
	ft_malloc_clear(&game->alloc);
	monster_free(&game->monsters);
	cloud_free(&game->clouds);
	mlx_destroy_window(game->mlx, game->win);
	mlx_destroy_display(game->mlx);
	free(game->player);
	free(game->mlx);
}
