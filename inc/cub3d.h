/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pau <pau@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 20:42:37 by pau               #+#    #+#             */
/*   Updated: 2025/03/11 20:42:43 by pau              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <errno.h>
# include <math.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <limits.h>
# include "../libft/libft.h"
# include "../get_next_line/get_next_line.h"
# include "../ft_printf/ft_printf.h"
# include "../mlx_linux/mlx.h"
# include "struct.h"
# include <X11/keysym.h>
# include <X11/X.h>

// textures && window
# define WIDTH 1280
# define HEIGHT 720
# define TEXTURE_WIDTH 64
# define TEXTURE_HEIGHT 64

# define KEY_ESC		65307
# define KEY_W			119
# define KEY_A			97
# define KEY_S			115
# define KEY_D			100
# define SPACE			32

# define KEY_UP			65362
# define KEY_DOWN		65364
# define KEY_L			65361
# define KEY_R			65363

# define SPEED			0.09
# define ROTATION		0.09
# define PI             3.14159264

# ifndef O_DIRECTORY
#  define O_DIRECTORY 00200000
# endif

int			parse(t_game *game, char **argv);
int			count_lines(char *file);
int			count_map_height(char **file, int i);
int			map_validity(t_game *game);
int			info_validity(t_texturedata textures);
int			render(t_game *game);
int			number_to_hex(char **number);
int			key_event(int key_code, t_game *game);
int			close_window(t_game *game);
void		init_data(t_game *game);
void		init_player(t_game *game);
void		init_cameraplane(t_game *game);
void		init_img(t_game *game);
void		copy_colors(t_game *game, char *line, int j);
void		copy_textures(t_game *game, char *line, int j);
void		copy_info(t_game *game, char *line, int j);
void		copy_map(t_game *game, char **file, int i);
void		fill_copy(t_game *game);
void		print_info(t_game *game);
void		print_array(char **array);
void		free_info(t_game *game);
void		free_array(char **array);
void		floodfill(char **map_dup, int x, int y);
void		duplicate_map(t_game *game);
void		raycasting(t_game *game);
void		draw_vline(t_game *game, int x);
void		put_pixel(t_game *game, int x, int y, int color);
void		clean_game(t_game *game);
void		destroy_images(t_game *game);
void		game_error(t_game *game, char *error);
char		*ft_strdup_no_nl(char *str);

#endif