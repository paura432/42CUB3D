/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pau <pau@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 19:56:15 by pau               #+#    #+#             */
/*   Updated: 2025/03/09 12:52:25 by pau              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	dda_algorithm(t_data *data)
{
	int	wall;

	wall = 0;
	while (wall == 0)
	{
		if (data->ray.side_dist.x < data->ray.side_dist.y)
		{
			data->ray.side_dist.x += data->ray.delta_dist.x;
			data->ray.pos.x += data->ray.step.x;
			data->ray.side = 0;
		}
		else
		{
			data->ray.side_dist.y += data->ray.delta_dist.y;
			data->ray.pos.y += data->ray.step.y;
			data->ray.side = 1;
		}
		if (data->dmap[data->ray.pos.y][data->ray.pos.x] == '1')
			wall = 1;
	}
}

static void	get_step(t_data *data)
{
	if (data->ray.dir.x < 0)
	{
		data->ray.step.x = -1;
		data->ray.side_dist.x = (data->pc.pos.x - data->ray.pos.x)
			* data->ray.delta_dist.x;
	}
	else
	{
		data->ray.step.x = 1;
		data->ray.side_dist.x = (data->ray.pos.x + 1.0 - data->pc.pos.x)
			* data->ray.delta_dist.x;
	}
	if (data->ray.dir.y < 0)
	{
		data->ray.step.y = -1;
		data->ray.side_dist.y = (data->pc.pos.y - data->ray.pos.y)
			* data->ray.delta_dist.y;
	}
	else
	{
		data->ray.step.y = 1;
		data->ray.side_dist.y = (data->ray.pos.y + 1.0 - data->pc.pos.y)
			* data->ray.delta_dist.y;
	}
}

static void	get_delta(t_data *data)
{
	if (data->ray.dir.x == 0)
		data->ray.delta_dist.x = INT_MAX;
	else
		data->ray.delta_dist.x = fabs(1 / data->ray.dir.x);
	if (data->ray.dir.y == 0)
		data->ray.delta_dist.y = INT_MAX;
	else
		data->ray.delta_dist.y = fabs(1 / data->ray.dir.y);
}

static void	init_raycast(t_data *data, int x)
{
	data->ray.pos.x = data->pc.pos.x;
	data->ray.pos.y = data->pc.pos.y;
	data->ray.cam_x = 2 * x / (double)WIDTH - 1;
	data->ray.dir.x = data->pc.dir.x
		+ data->pc.plane.x * data->ray.cam_x;
	data->ray.dir.y = data->pc.dir.y
		+ data->pc.plane.y * data->ray.cam_x;
}

void	raycasting(t_data *data)
{
	int	x;

	x = 0;
	while (x < WIDTH)
	{
		init_raycast(data, x);
		get_delta(data);
		get_step(data);
		dda_algorithm(data);
		if (data->ray.side == 0)
			data->ray.perpwalldist = ((data->ray.side_dist.x
						- data->ray.delta_dist.x));
		else
			data->ray.perpwalldist = ((data->ray.side_dist.y
						- data->ray.delta_dist.y));
		draw_vline(data, x);
		x++;
	}
}
