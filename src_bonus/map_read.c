/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_read.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: femorell <femorell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 15:24:51 by femorell          #+#    #+#             */
/*   Updated: 2023/03/17 15:48:06 by femorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long_bonus.h"

static void	map_size(t_game *game, int fd)
{
	char	c;
	int		temp_w;

	temp_w = 0;
	while (read(fd, &c, 1) > 0)
	{
		if (c == '\n')
		{
			game->size.y++;
			temp_w = 0;
		}
		else
			temp_w++;
		if (temp_w > game->size.x)
			game->size.x = temp_w;
	}
	close (fd);
}

static void	map_malloc(t_game *game, int fd)
{
	map_size(game, fd);
	if (game->size.y == 0 || game->size.x == 0)
		exit_error(0, "Error\nInvalid map. It's empty.", game);
}

char	*strjoin_free(char *s1, char *s2)
{
	char	*new;

	new = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (new);
}

char	**map_init(char *filename)
{
	char	*mapping;
	char	*temp;
	char	**map;
	int		fd;

	fd = open(filename, O_RDONLY);
	mapping = ft_strdup("");
	while (1)
	{
		temp = get_next_line(fd);
		if (temp == NULL)
			break ;
		mapping = strjoin_free(mapping, temp);
	}
	map = ft_split(mapping, '\n');
	free(mapping);
	close(fd);
	return (map);
}

void	map_read(t_game *game, char *filename)
{
	int	fd;
	int	len;

	game->size.y = 0;
	game->size.x = 0;
	fd = open(filename, O_RDONLY);
	if (fd <= 0)
		exit_error(0, "Error\nFailed to open the map", game);
	len = ft_strlen(filename);
	if (len < 4 || !ft_strnstr(&filename[len - 4], ".ber", 4))
		exit_error(0, "Error\nMap file extention is not .ber", game);
	map_malloc(game, fd);
	game->map = map_init(filename);
}
