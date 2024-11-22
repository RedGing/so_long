/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: femorell <femorell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 15:24:08 by femorell          #+#    #+#             */
/*   Updated: 2023/03/17 12:19:52 by femorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

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

void	free_game(t_game *game)
{	
	ft_img_clear(game->mlx, &game->img_alloc);
	ft_malloc_clear(&game->alloc);
	mlx_destroy_window(game->mlx, game->win);
	mlx_destroy_display(game->mlx);
	free(game->player);
	free(game->mlx);
}
