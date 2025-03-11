/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pau <pau@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 19:56:15 by pau               #+#    #+#             */
/*   Updated: 2025/03/10 17:18:20 by pau              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static void	dda_algorithm(t_game *game)
{
	int	wall;

	wall = 0;
	while (wall == 0)
	{
		if (game->ray.side_dist.x < game->ray.side_dist.y)
		{
			game->ray.side_dist.x += game->ray.delta_dist.x;
			game->ray.pos.x += game->ray.step.x;
			game->ray.side = 0;
		}
		else
		{
			game->ray.side_dist.y += game->ray.delta_dist.y;
			game->ray.pos.y += game->ray.step.y;
			game->ray.side = 1;
		}
		if (game->dmap[game->ray.pos.y][game->ray.pos.x] == '1')
			wall = 1;
	}
}

static void	get_step(t_game *game)
{
	if (game->ray.dir.x < 0)
	{
		game->ray.step.x = -1;
		game->ray.side_dist.x = (game->pc.pos.x - game->ray.pos.x)
			* game->ray.delta_dist.x;
	}
	else
	{
		game->ray.step.x = 1;
		game->ray.side_dist.x = (game->ray.pos.x + 1.0 - game->pc.pos.x)
			* game->ray.delta_dist.x;
	}
	if (game->ray.dir.y < 0)
	{
		game->ray.step.y = -1;
		game->ray.side_dist.y = (game->pc.pos.y - game->ray.pos.y)
			* game->ray.delta_dist.y;
	}
	else
	{
		game->ray.step.y = 1;
		game->ray.side_dist.y = (game->ray.pos.y + 1.0 - game->pc.pos.y)
			* game->ray.delta_dist.y;
	}
}

static void	get_delta(t_game *game)
{
	if (game->ray.dir.x == 0)
		game->ray.delta_dist.x = INT_MAX;
	else
		game->ray.delta_dist.x = fabs(1 / game->ray.dir.x);
	if (game->ray.dir.y == 0)
		game->ray.delta_dist.y = INT_MAX;
	else
		game->ray.delta_dist.y = fabs(1 / game->ray.dir.y);
}

static void	init_raycast(t_game *game, int x)
{
	game->ray.pos.x = game->pc.pos.x;
	game->ray.pos.y = game->pc.pos.y;
	game->ray.cam_x = 2 * x / (double)WIDTH - 1;
	game->ray.dir.x = game->pc.dir.x
		+ game->pc.plane.x * game->ray.cam_x;
	game->ray.dir.y = game->pc.dir.y
		+ game->pc.plane.y * game->ray.cam_x;
}

void	raycasting(t_game *game)
{
	int	x;

	x = 0;
	while (x < WIDTH)
	{
		init_raycast(game, x);
		get_delta(game);
		get_step(game);
		dda_algorithm(game);
		if (game->ray.side == 0)
			game->ray.perpwalldist = ((game->ray.side_dist.x
						- game->ray.delta_dist.x));
		else
			game->ray.perpwalldist = ((game->ray.side_dist.y
						- game->ray.delta_dist.y));
		draw_vline(game, x);
		x++;
	}
}
