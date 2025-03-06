/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pau <pau@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 10:32:45 by pau               #+#    #+#             */
/*   Updated: 2025/03/06 19:49:42 by pau              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void draw_map(t_game *game) {
    int y; 
	int	x;
    int pos_x;
	int pos_y;

    y = 0;
    pos_y = 0;
    while (game->map->map[y]) {
        x = 0;
        pos_x = 0;
        while (game->map->map[y][x]) {
            if (game->map->map[y][x] == '1') {
                draw_pixel(game, pos_x, pos_y, 0xFFFFFF); // Dibuja una pared
            } else if (game->map->map[y][x] == '0') {
                draw_pixel(game, pos_x, pos_y, 0x000000); // Dibuja un espacio vacío
            } else if (game->map->map[y][x] == 'N') {
                draw_pixel(game, pos_x, pos_y, 0x00FF0000); // Dibuja al jugador
            }
            pos_x += 8; // Ajusta el tamaño del bloque
            x++;
        }
        pos_y += 8; // Ajusta el tamaño del bloque
        y++;
    }
}

void draw_pixel(t_game *game, int pos_x, int pos_y, int color) 
{
    int pixel_index;

    // Calcular el índice del pixel en el buffer
    pixel_index = (pos_y * WIDTH + pos_x) * (game->img->bits_p_pixel / 8);

    // Asignar el color al pixel en el buffer
    if (pos_x >= 0 && pos_x < WIDTH && pos_y >= 0 && pos_y < HEIGHT) {
        game->buffer_data[pixel_index] = color & 0xFF;         // Blue
        game->buffer_data[pixel_index + 1] = (color >> 8) & 0xFF; // Green
        game->buffer_data[pixel_index + 2] = (color >> 16) & 0xFF; // Red
        if (game->img->bits_p_pixel == 32) {
            game->buffer_data[pixel_index + 3] = (color >> 24) & 0xFF; // Alpha
        }
    }
}

void draw_block(t_game *game, int x, int y, int color)
{
    int block_size;
    int block_x;
	int block_y;

	block_size = 2;
    block_y = y;
    while (block_y < y + block_size)
    {
        block_x = x;
        while (block_x < x + block_size)
        {
            mlx_pixel_put(game->img->mlx, game->img->mlx_win, block_x, block_y, color);
            block_x++;
        }
        block_y++;
    }
}

void	draw_line_until_wall(t_game *game, int color)
{
    int r;
	int eje;
	int suma;
    t_wall wall;

    r = -1;
    game->ray->ra = game->ply->pa - (DR * 15);
	eje = 0;
	suma = 0;
    while (++r < 60)
    {
        wall.distance = -1;
        
        // Detecta la colisión con la pared
        while (++wall.distance < MAX_DISTANCE)
        {
            wall.wall_x = game->map->player_x + 2 + cos(game->ray->ra) * wall.distance;
            wall.wall_y = game->map->player_y + 2 + sin(game->ray->ra) * wall.distance;
            
            if (game->map->map[(int)(wall.wall_y / 8)][(int)(wall.wall_x / 8)] == '1')
                break;  // Si choca con la pared, detiene el rayo
			mlx_pixel_put(game->img->mlx, game->img->mlx_win, wall.wall_x, wall.wall_y, color);
        }
		wall.ca = game->ply->pa - game->ray->ra;
		if (wall.ca < 0)
			wall.ca += 2 * PI;
		if (wall.ca > 2 * PI)
			wall.ca -= 2 * PI;
		wall.distance = wall.distance * cos(wall.ca);
		wall.lineH = ((240 * 16) / wall.distance);
		if (wall.lineH > 240)
			wall.lineH = 240;
		wall.lineO = (120 - wall.lineH) / 2;
		
		suma = wall.lineO;
		while (suma < wall.lineH)
		{
			draw_block(game, r + eje, game->map->height * 16 + wall.lineH + wall.lineO - suma, color);
			suma ++;
		}
		eje += 32;

        // Aumenta el ángulo para el siguiente rayo
        increase_degree(game);
    }
}

void	increase_degree(t_game *game)
{
	game->ray->ra += DR;
	if(game->ray->ra < 0)
		game->ray->ra += 2 * PI;
	else if(game->ray->ra > 2 * PI)
		game->ray->ra -= 2 * PI;
}
