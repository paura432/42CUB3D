/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pau <pau@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 20:40:31 by pau               #+#    #+#             */
/*   Updated: 2025/03/11 20:43:32 by pau              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	clean_game(t_game *game)
{
	if (game->file_data.file_cpy)
		free_array(game->file_data.file_cpy);
	if (game->map)
		free_array(game->map);
	if (game->dmap)
		free_array(game->dmap);
	free_info(game);
}

void	game_error(t_game *game, char *error)
{
	ft_printf(error);
	clean_game(game);
	exit(1);
}

static int	init_game(t_game *game)
{
	init_cameraplane(game);
	game->mlx = mlx_init();
	if (!game->mlx)
		return (0);
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "Cube3D");
	if (game->win == NULL)
		return (0);
	init_img(game);
	mlx_loop_hook(game->mlx, &render, game);
	mlx_hook(game->win, 2, 1L << 0, key_event, game);
	mlx_hook(game->win, 17, 1L << 17, close_window, game);
	mlx_loop(game->mlx);
	return (1);
}

static void	check_validity(t_game *game)
{
	duplicate_map(game);
	floodfill(game->dmap, game->pc.pos.x, game->pc.pos.y);
	if (!map_validity(game))
		game_error(game, "Error in map validation\n");
	else if (!info_validity(game->tex))
		game_error(game, "Error in textures validation\n");
	else
		ft_printf("File content is valid\n");
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
	{
		ft_printf("Error: one argument expected\n");
		return (1);
	}
	init_data(&game);
	if (!parse(&game, argv))
		game_error(&game, "Error during parsing\n");
	init_player(&game);
	check_validity(&game);
	if (!init_game(&game))
		game_error(&game, "Error initializing game\n");
	return (0);
}
