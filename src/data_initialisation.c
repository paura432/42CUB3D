/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_initialisation.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pau <pau@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 14:24:23 by vini              #+#    #+#             */
/*   Updated: 2025/03/11 20:40:49 by pau              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	init_img(t_game *game)
{
	int	i;

	i = 0;
	game->img[0].mlx_img = mlx_xpm_file_to_image(game->mlx, game->tex.n,
			&game->img[0].w, &game->img[0].h);
	game->img[1].mlx_img = mlx_xpm_file_to_image(game->mlx, game->tex.s,
			&game->img[1].w, &game->img[1].h);
	game->img[2].mlx_img = mlx_xpm_file_to_image(game->mlx, game->tex.e,
			&game->img[2].w, &game->img[2].h);
	game->img[3].mlx_img = mlx_xpm_file_to_image(game->mlx, game->tex.w,
			&game->img[3].w, &game->img[3].h);
	game->img[4].mlx_img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	while (i < 5)
	{
		game->img[i].ptr = mlx_get_data_addr(game->img[i].mlx_img,
				&game->img[i].bpp, &game->img[i].stride, &game->img[i].endian);
		i++;
	}
}

void	init_cameraplane(t_game *game)
{
	if (game->pc.point == 'N')
	{
		game->pc.plane.x = 0.66;
		game->pc.plane.y = 0;
	}
	if (game->pc.point == 'S')
	{
		game->pc.plane.x = -0.66;
		game->pc.plane.y = 0;
	}
	if (game->pc.point == 'W')
	{
		game->pc.plane.x = 0;
		game->pc.plane.y = 0.66;
	}
	if (game->pc.point == 'E')
	{
		game->pc.plane.x = 0;
		game->pc.plane.y = -0.66;
	}
}

static void	init_vectors(t_game *game, int i, int j)
{
	if (game->map[i][j] == 'N')
	{
		game->pc.pos = (t_vector){j, i};
		game->pc.dir = (t_vector){0, -1};
		game->pc.point = 'N';
	}
	else if (game->map[i][j] == 'S')
	{
		game->pc.pos = (t_vector){j, i};
		game->pc.dir = (t_vector){0, 1};
		game->pc.point = 'S';
	}
	else if (game->map[i][j] == 'E')
	{
		game->pc.pos = (t_vector){j, i};
		game->pc.dir = (t_vector){1, 0};
		game->pc.point = 'E';
	}
	else if (game->map[i][j] == 'W')
	{
		game->pc.pos = (t_vector){j, i};
		game->pc.dir = (t_vector){-1, 0};
		game->pc.point = 'W';
	}
}

void	init_player(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	game->pc.fov = 0;
	game->pc.dir.x = 0;
	game->pc.dir.y = 0;
	game->pc.pos.x = 0;
	game->pc.pos.y = 0;
	while (game->map[i] != NULL)
	{
		while (game->map[i][j] != '\0')
		{
			init_vectors(game, i, j);
			j++;
		}
		i++;
		j = 0;
	}
}

void	init_data(t_game *game)
{
	int	i;

	i = 0;
	game->map_height = 0;
	game->file_data.lines = 0;
	game->map = NULL;
	game->dmap = NULL;
	game->tex.n = NULL;
	game->tex.s = NULL;
	game->tex.e = NULL;
	game->tex.w = NULL;
	game->tex.f = NULL;
	game->tex.c = NULL;
	while (i < 5)
	{
		game->img[i].mlx_img = NULL;
		game->img[i].ptr = NULL;
		i++;
	}
}
