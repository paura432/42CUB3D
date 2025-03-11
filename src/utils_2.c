/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pau <pau@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 13:34:07 by vini              #+#    #+#             */
/*   Updated: 2025/03/10 17:19:02 by pau              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	destroy_images(t_game *game)
{
	int	i;

	i = 0;
	if (game->mlx)
	{
		while (i < 5)
		{
			if (game->img[i].mlx_img)
				mlx_destroy_image(game->mlx, game->img[i].mlx_img);
			i++;
		}
	}
}

int	close_window(t_game *game)
{
	clean_game(game);
	destroy_images(game);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	exit(0);
}

int	number_to_hex(char **number)
{
	int	hex;
	int	r;
	int	g;
	int	b;

	r = ft_atoi(number[0]);
	g = ft_atoi(number[1]);
	b = ft_atoi(number[2]);
	hex = r;
	hex = (hex << 8) + g;
	hex = (hex << 8) + b;
	return (hex);
}

void	duplicate_map(t_game *game)
{
	int	i;

	i = 0;
	game->dmap = ft_calloc(game->map_height + 1, sizeof(char *));
	if (!game->dmap)
		return ;
	while (i < game->map_height)
	{
		game->dmap[i] = ft_strdup(game->map[i]);
		i++;
	}
}

void	floodfill(char **map_dup, int x, int y)
{
	map_dup[y][x] = 'x';
	if (y > 0 && map_dup[y - 1][x] == '0' && map_dup[y - 1][x] != 'x')
		floodfill(map_dup, x, y - 1);
	if (map_dup[y][x + 1] != '\0'
		&& map_dup[y][x + 1] == '0' && map_dup[y][x + 1] != 'x')
		floodfill(map_dup, x + 1, y);
	if (map_dup[y + 1] != NULL
		&& map_dup[y + 1][x] == '0' && map_dup[y + 1][x] != 'x')
		floodfill(map_dup, x, y + 1);
	if (x > 0 && map_dup[y][x - 1] == '0' && map_dup[y][x - 1] != 'x')
		floodfill(map_dup, x - 1, y);
}
