/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pau <pau@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 17:53:53 by pramos            #+#    #+#             */
/*   Updated: 2025/02/17 16:02:06 by pau              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	free_list(t_game *game)
{
	mlx_clear_window(game->img->mlx, game->img->mlx_win);
	mlx_destroy_window(game->img->mlx, game->img->mlx_win);
	free(game->img);
	free(game->ply);
	free(game->map);
	free(game->ray);
	free(game->buffer_data);
	exit(0);
}

void	free_matriz(char **matriz)
{
	int	i;

	i = 0;
	while (matriz[i])
		free(matriz[i++]);
	free(matriz);
}