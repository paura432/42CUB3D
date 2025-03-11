/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pau <pau@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 22:14:21 by pramos            #+#    #+#             */
/*   Updated: 2025/03/11 20:16:57 by pau              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static void	rotate(t_game *game, double speed)
{
	double	aux_dir;
	double	aux_plane;

	aux_dir = game->pc.dir.x;
	aux_plane = game->pc.plane.x;
	game->pc.dir.x = game->pc.dir.x * cos(speed) - game->pc.dir.y * sin(speed);
	game->pc.dir.y = aux_dir * sin(speed) + game->pc.dir.y * cos(speed);
	game->pc.plane.x = game->pc.plane.x * cos(speed)
		- game->pc.plane.y * sin(speed);
	game->pc.plane.y = aux_plane * sin(speed)
		+ game->pc.plane.y * cos(speed);
}

static void	move(t_game *game, double x, double y, char sign)
{
	if (sign == '+')
	{
		if (game->dmap[(int)game->pc.pos.y][(int)(game->pc.pos.x + x)] != '1')
			game->pc.pos.x += x;
		if (game->dmap[(int)(game->pc.pos.y + y)][(int)game->pc.pos.x] != '1')
			game->pc.pos.y += y;
	}
	else if (sign == '-')
	{
		if (game->dmap[(int)game->pc.pos.y][(int)(game->pc.pos.x - x)] != '1')
			game->pc.pos.x -= x;
		if (game->dmap[(int)(game->pc.pos.y - y)][(int)game->pc.pos.x] != '1')
			game->pc.pos.y -= y;
	}
}

int	key_event(int key, t_game *game)
{
	if (key == KEY_ESC)
		close_window(game);
	else if (key == KEY_W)
		move(game, game->pc.dir.x * SPEED, game->pc.dir.y * SPEED, '+');
	else if (key == KEY_S)
		move(game, game->pc.dir.x * SPEED, game->pc.dir.y * SPEED, '-');
	else if (key == KEY_A)
		move(game, game->pc.plane.x * SPEED, game->pc.plane.y * SPEED, '-');
	else if (key == KEY_D)
		move(game, game->pc.plane.x * SPEED, game->pc.plane.y * SPEED, '+');
	else if ((key == KEY_L && (game->pc.point == 'N' || game->pc.point == 'S'))
		|| (key == KEY_R && (game->pc.point == 'E' || game->pc.point == 'W')))
		rotate(game, -ROTATION);
	else if ((key == KEY_L && (game->pc.point == 'E' || game->pc.point == 'W'))
		|| (key == KEY_R && (game->pc.point == 'N' || game->pc.point == 'S')))
		rotate(game, ROTATION);
	return (0);
}
