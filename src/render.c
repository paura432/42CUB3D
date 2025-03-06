/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pau <pau@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 20:57:43 by pau               #+#    #+#             */
/*   Updated: 2025/02/17 16:30:00 by pau              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"
int render(t_game *game) {
    void *img_buffer;
    int bits_per_pixel;
    int size_line;
    int endian;

    // Crear un nuevo buffer de imagen
    img_buffer = mlx_new_image(game->img->mlx, WIDTH, HEIGHT);
    if (!img_buffer) {
        fprintf(stderr, "Error: Failed to create image buffer\n");
        return -1; // Manejo de error
    }
    
    // Obtener la dirección del buffer de datos
    game->buffer_data = mlx_get_data_addr(img_buffer, &bits_per_pixel, &size_line, &endian);

    // Limpiar el buffer
    ft_memset(game->buffer_data, 0, WIDTH * HEIGHT * (bits_per_pixel / 8));

    // Dibujar el mapa en el buffer
    draw_map(game);
    draw_pixel(game, (int)game->map->player_x, (int)game->map->player_y, 0x00FF0000); // Dibuja al jugador
    draw_line_until_wall(game, 0x00FF00); // Dibuja la línea hasta la pared
    
    // Poner el buffer en la ventana
    mlx_put_image_to_window(game->img->mlx, game->img->mlx_win, img_buffer, 0, 0);
    
    // Destruir el buffer después de usarlo
    mlx_destroy_image(game->img->mlx, img_buffer);

    return (0);
}


// // void draw_sky_and_floor(t_game *game)
// // {
// //     int x;
// //     int y;

// //     x = 0;
// // 	while (x < WIDTH)
// // 	{
// // 		y = 0;
// // 		while (y < HEIGHT)
// // 		{
// // 			if (y < HEIGHT / 2)
// // 				mlx_pixel_put(game->img->mlx, game->img->mlx_win, x, y, 
// // 				ft_atoi(rgb_to_hex(game->colors->ceiling_r, game->colors->ceiling_g,
// // 				game->colors->ceiling_b)));
// // 			else
// // 				mlx_pixel_put(game->img->mlx, game->img->mlx_win, x, y,
// // 				ft_atoi(rgb_to_hex(game->colors->floor_r, game->colors->floor_g,
// // 				game->colors->floor_b)));
// // 			y++;
// // 		}
// // 		++x;
// // 	}
// // }
