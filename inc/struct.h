/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pau <pau@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 11:04:19 by pau               #+#    #+#             */
/*   Updated: 2025/03/11 20:42:18 by pau              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef struct s_intvector
{
	int	x;
	int	y;
}	t_intvector;

typedef struct s_vector
{
	double	x;
	double	y;
}	t_vector;

typedef struct s_ray
{
	int			side;
	int			line_start;
	int			line_end;
	double		cam_x;
	double		perpwalldist;
	double		wall_x;
	double		tex_pos;
	double		tex_step;
	t_intvector	pos;
	t_intvector	step;
	t_intvector	tex;
	t_vector	dir;
	t_vector	delta_dist;
	t_vector	side_dist;
}	t_ray;

typedef struct s_img
{
	void	*mlx_img;
	void	*ptr;
	int		w;
	int		h;
	int		bpp;
	int		stride;
	int		endian;
}	t_img;

typedef struct s_player
{
	char		point;
	float		fov;
	t_vector	pos;
	t_vector	dir;
	t_vector	plane;
}	t_player;

typedef struct s_texturedata
{
	char	*n;
	char	*s;
	char	*e;
	char	*w;
	char	**f;
	char	**c;
}	t_texturedata;

typedef struct s_filedata
{
	int		lines;
	int		fd;
	char	**file_cpy;
}	t_filedata;

typedef struct s_game
{
	int				map_height;
	void			*mlx;
	void			*win;
	char			**map;
	char			**dmap;
	t_filedata		file_data;
	t_texturedata	tex;
	t_player		pc;
	t_img			img[5];
	t_ray			ray;
}	t_game;

#endif