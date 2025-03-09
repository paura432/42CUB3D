/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pau <pau@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 20:40:31 by pau               #+#    #+#             */
/*   Updated: 2025/03/09 12:49:20 by pau              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	clean_game(t_data *data)
{
	if (data->file_data.file_cpy)
		free_array(data->file_data.file_cpy);
	if (data->map)
		free_array(data->map);
	if (data->dmap)
		free_array(data->dmap);
	free_info(data);
}

void	game_error(t_data *data, char *error)
{
	ft_printf(error);
	clean_game(data);
	// destroy_images(data);
	// if (data->win)
	// 	mlx_destroy_window(data->mlx, data->win);
	// if (data->mlx)
	// {
	// 	mlx_destroy_display(data->mlx);
	// 	free(data->mlx);
	// }
	exit(1);
}

static int	init_game(t_data *data)
{
	init_cameraplane(data);
	data->mlx = mlx_init();
	if (!data->mlx)
		return (0);
	data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "Cube3D");
	if (data->win == NULL)
		return (0);
	init_img(data);
	mlx_loop_hook(data->mlx, &render, data);
	mlx_hook(data->win, 2, 1L << 0, key_event, data);
	mlx_hook(data->win, 17, 1L << 17, close_window, data);
	mlx_loop(data->mlx);
	return (1);
}

static void	check_validity(t_data *data)
{
	duplicate_map(data);
	floodfill(data->dmap, data->pc.pos.x, data->pc.pos.y);
	if (!map_validity(data))
		game_error(data, "Error in map validation\n");
	else if (!info_validity(data->tex))
		game_error(data, "Error in textures validation\n");
	else
		ft_printf("File content is valid\n");
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
	{
		ft_printf("Error: one argument expected\n");
		return (1);
	}
	init_data(&data);
	if (!parse(&data, argv))
		game_error(&data, "Error during parsing\n");
	init_player(&data);
	check_validity(&data);
	if (!init_game(&data))
		game_error(&data, "Error initializing game\n");
	return (0);
}
