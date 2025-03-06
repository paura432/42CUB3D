/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pau <pau@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 11:04:19 by pau               #+#    #+#             */
/*   Updated: 2025/02/17 15:46:12 by pau              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef struct s_ply 
{
    int 		pos_x;        // Equivalente a x en tu estructura
    int 		pos_y;        // Equivalente a y en tu estructura
    double 		ra;     // Equivalente a dir
    float 		fov;        // Equivalente a fov
    int 		rotation;     // Equivalente a rot
    float       px;
    float       py;
    float       pdy;
    float       pdx;
    float       pa;
    int 		m_l;      // Equivalente a mov_lr
    int 		m_r;      // Equivalente a mov_ud
} t_ply;

typedef struct s_colors {
    int floor_hex;
    int floor_r;
    int floor_g;
    int floor_b;
    int ceiling_hex;
    int ceiling_r;
    int ceiling_g;
    int ceiling_b;
} t_colors;

typedef struct s_ray 
{
    double 		ra;     // Equivalente a dir_ray
    double 		dist;  // Equivalente a dist
    int 		hit;     // Equivalente a wall_hit
    int         add_x;
    int         add_y;
    int         sub_x;
    int         sub_y;
} t_ray;

typedef struct s_map 
{
    char 		**map;      // Equivalente a map
    float 		player_x;     // Equivalente a pos_player_x
    float 		player_y;
	int			draw_x;
	int			draw_y;    // Equivalente a pos_player_y
	int 		color;
    int 		width;        // Equivalente a ancho
    int 		height;       // Equivalente a alto
} t_map;

typedef struct s_image
{
	void	     *img;
	void	     *mlx;
	void	     *mlx_win;
	char         *addr;
	int		     bits_p_pixel;
	int		     line_len;
	int		     endian;
	int          win_width;
	int          win_height;
	int          x_player;
	int          y_player;
	char	     **map;
}				t_image;

typedef struct s_texture {
    void *img; // Imagen cargada por MiniLibX
    char *addr; // Dirección de memoria de los píxeles
    int bits_p_pixel; // Bits por píxel
    int line_len; // Longitud de línea en bytes
    int endian; // Orden de bytes
    int win_width; // Ancho de la textura
    int win_height; // Alto de la textura
} t_texture;

typedef struct s_game 
{
    t_image 	*img;  
    t_ray		*ray;         
    t_map		*map;          
    t_ply		*ply;    
    t_colors    *colors;
    char        *buffer_data; // Agregar buffer_data aquí
} t_game;

typedef struct s_line
{
	float       start_x;
	float       start_y;
	float       end_x;
	float       end_y;
	float       intermediate_x;
	float       intermediate_y;
}               t_line;

typedef struct s_wall
{
	int     wall_height;
	int     wall_top;
	int     wall_bottom;
	int     wall_y;
	int		wall_x;
	float	lineH;
	float	lineO;
	float 	distance;
	float 	ca;
	int 	draw_y;
}               t_wall;

#endif