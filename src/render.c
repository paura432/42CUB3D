/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pau <pau@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 20:57:43 by pau               #+#    #+#             */
/*   Updated: 2025/03/11 20:18:34 by pau              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	put_pixel(t_game *game, int x, int y, int color)
{
	char	*pixel;

	if (y < 0 || y > HEIGHT - 1 || x < 0
		|| x > WIDTH - 1)
		return ;
	pixel = (game->img[4].ptr + (y * game->img[4].stride
				+ x * (game->img[4].bpp / 8)));
	*(int *)pixel = color;
}

static void	render_background(t_game *game)
{
	int	x;
	int	y;

	x = 0;
	while (x < WIDTH)
	{
		y = 0;
		while (y < HEIGHT)
		{
			if (y < HEIGHT / 2)
				put_pixel(game, x, y, number_to_hex(game->tex.c));
			else
				put_pixel(game, x, y, number_to_hex(game->tex.f));
			y++;
		}
		++x;
	}
}

int	render(t_game *game)
{
	render_background(game);
	raycasting(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img[4].mlx_img, 0, 0);
	return (0);
}
