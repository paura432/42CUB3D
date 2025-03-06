/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pau <pau@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 22:14:21 by pramos            #+#    #+#             */
/*   Updated: 2025/02/17 15:41:15 by pau              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	key_press(int key_code, t_game *game)
{
    // game->map->color = 0x000000;
	// draw_pixel(game, (int)game->map->player_x, (int)game->map->player_y, 4);
	// draw_line_until_wall(game, 0x000000);
	if (key_code == 100)
		right(game);
	if (key_code == 97)
		left(game);
	if (key_code == 119)
		up(game);
	if (key_code == 115)
		down(game);
	if (key_code == 65307)
	{
		ft_printf("GAME FINISHED\n");
		free_list(game);
	}
    // game->map->color = 0x00FF0000;
	// draw_line_until_wall(game, 0x00FF00);
	// draw_pixel(game, (int)game->map->player_x, (int)game->map->player_y, 4);
    // draw_map(game);
	return (0);
}

int check_collision(t_game *game, float new_x, float new_y)
{
    if (game->map->map[(int)(new_y) / 8][(int)(new_x) / 8] == '1' ||
        game->map->map[(int)(new_y) / 8][(int)(new_x + 4) / 8] == '1' ||
        game->map->map[(int)(new_y + 4) / 8][(int)(new_x) / 8] == '1' ||
        game->map->map[(int)(new_y + 4) / 8][(int)(new_x + 4) / 8] == '1')
        return (1);

    return (0);
}

void right(t_game *game)
{
    game->ply->pa -= 0.1;
    if (game->ply->pa < 0)
        game->ply->pa += 2 * PI;
    game->ply->pdx = cos(game->ply->pa) * 4;
    game->ply->pdy = sin(game->ply->pa) * 4;
}

void left(t_game *game)
{
    game->ply->pa += 0.1;
    if (game->ply->pa > 2 * PI)
        game->ply->pa -= 2 * PI;
    game->ply->pdx = cos(game->ply->pa) * 4;
    game->ply->pdy = sin(game->ply->pa) * 4;
}

void up(t_game *game)
{
    float new_x;
    float new_y;

	new_x = game->map->player_x + game->ply->pdx;
	new_y = game->map->player_y + game->ply->pdy;

    if (!check_collision(game, new_x, game->map->player_y))
        game->map->player_x = new_x;
    if (!check_collision(game, game->map->player_x, new_y))
        game->map->player_y = new_y;
}

void down(t_game *game)
{
    float new_x;
    float new_y;

	new_x = game->map->player_x - game->ply->pdx;
	new_y = game->map->player_y - game->ply->pdy;
    if (!check_collision(game, new_x, game->map->player_y))
        game->map->player_x = new_x;
    if (!check_collision(game, game->map->player_x, new_y))
        game->map->player_y = new_y;
}