/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pau <pau@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 20:42:37 by pau               #+#    #+#             */
/*   Updated: 2025/02/16 14:57:17 by pau              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../mlx_linux/mlx.h"
# include "struct.h"
# include "../libft/libft.h"
# include "../get_next_line/get_next_line.h"
# include "../ft_printf/ft_printf.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <time.h>
# include <pthread.h>
# include <math.h>
# include <x86intrin.h>
# include <semaphore.h>
# define PI 3.1415926535
# define DR 0.0174533
# define WIDTH 1900 // screen width
# define HEIGHT 1000 // screen height
# define FOV 60 // field of view
# define ROTATION_SPEED 0.045 // rotation speed
# define PLAYER_SPEED 4 // player speed
# define MAX_DISTANCE 800

//cub3d
int	    close_window(t_game	*game);
void	start_values(t_game *game, char **argv);

//read
int	    count_lines(char *argv);
int	    count_bytes(char *argv);
char	**ft_read(char **argv);

//flood_fill
int	    count_bytes_w_fd(char *map);
int	    count_lines_w_fd(char **map);
void	f_fill_p2e(char **flood_map, char target, int y, int x);

//free
void	free_list(t_game *game);
void	free_matriz(char **matriz);


// raycasting
void raycasting(t_game *game);
float get_horizontal_intersection(t_game *game, float ra);
float get_vertical_intersection(t_game *game, float ra);
void draw_wall_column(t_game *game, int x, int height, int color);

//colors.c
int extract_rgb(char *line, int *r, int *g, int *b);
int extract_floor(char **map, t_colors *colors);
int extract_ceiling(char **map, t_colors *colors);
t_colors *get_colors(char **map);
char *ft_strdup_no_hex(char **rgb);
int ft_atoi_base(const char *str, int base, int result, int sign);


// //raycasting
// void    raycasting(t_image *img);

// //move.c
int	    key_press(int key_code, t_game *game);
int	    move_check(t_game *game);
void	right(t_game *game);
void	up(t_game *game);
void	left(t_game *game);
void	down(t_game *game);
int	    check_pixel(t_game *game, int add_x, int add_y);


// //draw.c
void    draw_map(t_game *game);
void    draw_pixel(t_game *game, int pos_x, int pos_y, int pixel);
void    draw_line(t_game *game, int color, int length);
void    draw_line_until_wall(t_game *game, int color);
void    increase_degree(t_game *game);
void    draw_block(t_game *game, int x, int y, int color);
void	search_ply(t_game *game);

//render
int    render(t_game *game);
void    draw_sky_and_floor(t_game *game);
int    number_to_hex(int r, int g, int b);

#endif