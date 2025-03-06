/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pau <pau@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 20:40:31 by pau               #+#    #+#             */
/*   Updated: 2025/02/17 15:58:16 by pau              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	close_window(t_game	*game)
{
	ft_printf("GAME FINISHED\n");
	free(game);
	return (0);
}

void	start_values(t_game *game, char **argv)
{
	game->img = malloc(sizeof(t_image));
	game->map = malloc(sizeof(t_map));
	game->ply = malloc(sizeof(t_ply));
	game->ray = malloc(sizeof(t_ray));

	game->buffer_data = NULL;
	game->ply->pdx = 2.0;
	game->ply->pdy = 0.0;
	game->ply->pa = 0.0;	
	game->map->map = ft_read(argv);
	game->map->width = count_bytes_w_fd(game->map->map[0]);
	game->map->height = count_lines_w_fd(game->map->map);
	// game->colors = get_colors(game->map->map);
}

int main(int argc, char **argv)
{
	t_game game;
	
	if(argc > 2)
		return(0);
	start_values(&game, argv);
	game.img->mlx = mlx_init();
	game.img->mlx_win = mlx_new_window(game.img->mlx, WIDTH,
 			HEIGHT, "Cub3d");

	// draw_map(&game);
	// mlx_loop_hook(game.img->mlx, &render, &game);
	mlx_loop_hook(game.img->mlx, render, &game);
	mlx_hook(game.img->mlx_win, 17, 0, close_window, game.img);
	mlx_hook(game.img->mlx_win, 2, 1L << 0, key_press, &game);
	mlx_loop(game.img->mlx);
}
// int	main(int argc, char **argv)
// {
// 	t_image	img;

// 	if(argc == 0)
// 		return(0);
// 	img.map = ft_read(argv);
// 	start_values(&img);
// 	img.x_player = (count_bytes_w_fd(img.map[0]) * 64) / 2;
// 	img.y_player = (count_lines_w_fd(img.map) * 64) / 2;
// 	img.mlx = mlx_init();
// 	printf("%i\n", count_lines_w_fd(img.map) * 64);
// 	img.mlx_win = mlx_new_window(img.mlx, count_bytes_w_fd(img.map[0]) * 64 * 2,
// 			count_lines_w_fd(img.map) * 64, "cub3d");
// 	draw_map(&img);
// 	img.y_pixel = img.y_player;
//     img.x_pixel = img.x_player;
// 	mlx_hook(img.mlx_win, 17, 0, close_window, &img);
// 	mlx_hook(img.mlx_win, 2, 1L << 0, key_press, &img);
// 	mlx_loop(img.mlx);
// }







// int	key_press(int key_code, t_image *img)
// {
// 	if (key_code == 100)
// 		right(img);
// 	if (key_code == 97)
// 		left(img);
// 	move_check(img);
// 	if (key_code == 119)
// 		up(img);
// 	if (key_code == 115)
// 		down(img);
// 	if (key_code == 65307)
// 	{
// 		ft_printf("GAME FINISHED\n");
// 		free_list(img);
// 	}
// }









// void		start_values(t_image *img)
// {
// 	img->player = (t_player *)malloc(sizeof(t_player));
// 	if (img->player == NULL)
// 		return (free_list(img));
// 	img->ray = (t_raycasting *)malloc(sizeof(t_raycasting));
// 	if (img->ray == NULL)
// 		return (free_list(img));
// 	img->check = (t_move_check *)malloc(sizeof(t_move_check));
// 	if (img->check == NULL)
// 		return (free_list(img));
// 	img->player->px = img->x_player;
// 	img->player->py = img->y_player;
// 	img->player->pdx = 5.0;
// 	img->player->pdy = 0.0;
// 	img->player->pa = 0.0;

// 	img->win_width = count_bytes_w_fd(img->map[0]);
// 	img->win_height = count_lines_w_fd(img->map);
// }

