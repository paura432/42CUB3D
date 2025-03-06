
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


#include "../inc/cub3d.h"

void	draw_map(t_game *game)
{
	int y;
	int x;
	int pos_x;
	int pos_y;

	y = -1;
	pos_y = 0;
	while(game->map->map[++y])
	{
		x = -1;
		pos_x = 0;
		while(game->map->map[y][++x])
		{
			if (game->map->map[y][x] == '1')
			{
				game->map->color = 0xFFFFFF;
				draw_pixel(game, pos_x, pos_y, 0xFFFFFF);
			}
			if (game->map->map[y][x] == 'N')
			{
				game->map->color = 0x00FF0000;
				game->map->map[y][x] = '0';
				game->map->player_x = (float)pos_x;
				game->map->player_y = (float)pos_y;
				draw_pixel(game, pos_x, pos_y, 0x00FF0000);
			}
			pos_x += 8;
		}
		pos_y += 8;
	}
	return ;
}

void draw_pixel(t_game *game, int pos_x, int pos_y, int color)
{
    int pixel_index;

    // Calcular el índice del pixel en el buffer
    pixel_index = (pos_y * WIDTH + pos_x) * (game->img->bits_p_pixel / 8);

    // Asignar el color al pixel en el buffer
    if (pos_x >= 0 && pos_x < WIDTH && pos_y >= 0 && pos_y < HEIGHT)
    {
        // Asumiendo que el formato de color es 0x00RRGGBB
        game->buffer_data[pixel_index] = color & 0xFF;         // Blue
        game->buffer_data[pixel_index + 1] = (color >> 8) & 0xFF; // Green
        game->buffer_data[pixel_index + 2] = (color >> 16) & 0xFF; // Red
        // Si estás usando un formato de 32 bits, puedes establecer el valor alpha
        if (game->img->bits_p_pixel == 32)
        {
            game->buffer_data[pixel_index + 3] = (color >> 24) & 0xFF; // Alpha
        }
    }
}

void draw_block(t_game *game, int x, int y, int color)
{
    int block_size;
    int block_x;
	int block_y;

	block_size = 2;
    block_y = y;
    while (block_y < y + block_size)
    {
        block_x = x;
        while (block_x < x + block_size)
        {
            mlx_pixel_put(game->img->mlx, game->img->mlx_win, block_x, block_y, color);
            block_x++;
        }
        block_y++;
    }
}

void	draw_line_until_wall(t_game *game, int color)
{
    int r;
	int eje;
	int suma;
    t_wall wall;

    r = -1;
    game->ray->ra = game->ply->pa - (DR * 15);
	eje = 0;
	suma = 0;
    while (++r < 60)
    {
        wall.distance = -1;
        
        // Detecta la colisión con la pared
        while (++wall.distance < MAX_DISTANCE)
        {
            wall.wall_x = game->map->player_x + 2 + cos(game->ray->ra) * wall.distance;
            wall.wall_y = game->map->player_y + 2 + sin(game->ray->ra) * wall.distance;
            
            if (game->map->map[(int)(wall.wall_y / 8)][(int)(wall.wall_x / 8)] == '1')
                break;  // Si choca con la pared, detiene el rayo
			mlx_pixel_put(game->img->mlx, game->img->mlx_win, wall.wall_x, wall.wall_y, color);
        }
		wall.ca = game->ply->pa - game->ray->ra;
		if (wall.ca < 0)
			wall.ca += 2 * PI;
		if (wall.ca > 2 * PI)
			wall.ca -= 2 * PI;
		wall.distance = wall.distance * cos(wall.ca);
		wall.lineH = ((600 * 16) / wall.distance);
		if (wall.lineH > 600)
			wall.lineH = 600;
		wall.lineO = (300 - wall.lineH) / 2;
		
		suma = wall.lineO;
		while (suma < wall.lineH)
		{
			draw_block(game, r + eje, game->map->height * 16 + wall.lineH + wall.lineO - suma, color);
			suma ++;
		}
		eje += 32;

        // Aumenta el ángulo para el siguiente rayo
        increase_degree(game);
    }
}

void	increase_degree(t_game *game)
{
	game->ray->ra += DR;
	if(game->ray->ra < 0)
		game->ray->ra += 2 * PI;
	else if(game->ray->ra > 2 * PI)
		game->ray->ra -= 2 * PI;
}


# include "../inc/cub3d.h"

int	count_bytes_w_fd(char *map)
{
	int	x;

	x = 0;
	while (map[x] != '\0' && map[x] != '\n')
		x++;
	return (x);
}

int	count_lines_w_fd(char **map)
{
	int	y;
	int	x;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x] != '\0' && map[y][x] != '\n')
			x++;
		y++;
	}
	return (y);
}

void	f_fill_p2e(char **flood_map, char target, int y, int x)
{
	if (y < 0 || x < 0 || y >= count_lines_w_fd(flood_map)
		|| x >= count_bytes_w_fd(flood_map[0]))
		return ;
	if (flood_map[y][x] == 'F' || flood_map[y][x] == target)
		return ;
	flood_map[y][x] = 'F';
	f_fill_p2e(flood_map, target, y - 1, x);
	f_fill_p2e(flood_map, target, y + 1, x);
	f_fill_p2e(flood_map, target, y, x - 1);
	f_fill_p2e(flood_map, target, y, x + 1);
}


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


#include "../inc/cub3d.h"

int	key_press(int key_code, t_game *game)
{
    // game->map->color = 0x000000;
	// draw_pixel(game, (int)game->map->player_x, (int)game->map->player_y, 4);
	// draw_line_until_wall(game, 0x000000);
	if (key_code == 100)
		right(game);
	if (key_code == 97)
		left(game);
	if (key_code == 119)
		up(game);
	if (key_code == 115)
		down(game);
	if (key_code == 65307)
	{
		ft_printf("GAME FINISHED\n");
		free_list(game);
	}
    // game->map->color = 0x00FF0000;
	// draw_line_until_wall(game, 0x00FF00);
	// draw_pixel(game, (int)game->map->player_x, (int)game->map->player_y, 4);
    // draw_map(game);
	return (0);
}

int check_collision(t_game *game, float new_x, float new_y)
{
    if (game->map->map[(int)(new_y) / 8][(int)(new_x) / 8] == '1' ||
        game->map->map[(int)(new_y) / 8][(int)(new_x + 4) / 8] == '1' ||
        game->map->map[(int)(new_y + 4) / 8][(int)(new_x) / 8] == '1' ||
        game->map->map[(int)(new_y + 4) / 8][(int)(new_x + 4) / 8] == '1')
        return (1);

    return (0);
}

void right(t_game *game)
{
    game->ply->pa -= 0.1;
    if (game->ply->pa < 0)
        game->ply->pa += 2 * PI;
    game->ply->pdx = cos(game->ply->pa) * 4;
    game->ply->pdy = sin(game->ply->pa) * 4;
}

void left(t_game *game)
{
    game->ply->pa += 0.1;
    if (game->ply->pa > 2 * PI)
        game->ply->pa -= 2 * PI;
    game->ply->pdx = cos(game->ply->pa) * 4;
    game->ply->pdy = sin(game->ply->pa) * 4;
}

void up(t_game *game)
{
    float new_x;
    float new_y;

	new_x = game->map->player_x + game->ply->pdx;
	new_y = game->map->player_y + game->ply->pdy;

    if (!check_collision(game, new_x, game->map->player_y))
        game->map->player_x = new_x;
    if (!check_collision(game, game->map->player_x, new_y))
        game->map->player_y = new_y;
}

void down(t_game *game)
{
    float new_x;
    float new_y;

	new_x = game->map->player_x - game->ply->pdx;
	new_y = game->map->player_y - game->ply->pdy;
    if (!check_collision(game, new_x, game->map->player_y))
        game->map->player_x = new_x;
    if (!check_collision(game, game->map->player_x, new_y))
        game->map->player_y = new_y;
}


#include "../inc/cub3d.h"

int	count_lines(char *argv)
{
	int		fd;
	int		lines;
	int		bytes;
	char	character[1];

	fd = open(argv, O_RDONLY);
	lines = 1;
	bytes = 1;
	while (bytes != 0)
	{
		bytes = read(fd, character, 1);
		if (character[0] == '\n')
			lines++;
	}
	close(fd);
	return (lines - 1);
}

int	count_bytes(char *argv)
{
	int		fd;
	int		bytes;
	int		bytes_read;
	char	character[1];

	fd = open(argv, O_RDONLY);
	bytes = 0;
	bytes_read = 1;
	while (bytes_read != 0 && character[0] != '\n')
	{
		bytes_read = read(fd, character, 1);
		if (character[0] != '\n')
			bytes++;
	}
	close(fd);
	return (bytes);
}

char	**ft_read(char **argv)
{
	int		i;
	int		lines;
	int		fd;
	char	**map;

	i = 0;
	lines = count_lines(argv[1]);
	if (lines < 2)
		return (0);
	map = (char **)malloc(sizeof(char *) * (count_lines(argv[1]) + 1));
	fd = open(argv[1], O_RDONLY);
	while (lines-- > 0)
		map[i++] = get_next_line(fd);
	map[i] = NULL;
	close(fd);
	return (map);
}


int render(t_game *game)
{
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
    
    game->buffer_data = mlx_get_data_addr(img_buffer, &bits_per_pixel, &size_line, &endian);

    // Limpiar el buffer
    ft_memset(game->buffer_data, 0, WIDTH * HEIGHT * (bits_per_pixel / 8));

    // Dibujar el mapa en el buffer
    draw_map(game);
    draw_pixel(game, (int)game->map->player_x, (int)game->map->player_y, 4);
    draw_line_until_wall(game, 0x00FF00); // Color de la línea
    
    // Poner el buffer en la ventana
    mlx_put_image_to_window(game->img->mlx, game->img->mlx_win, img_buffer, 0, 0);
    
    // Destruir el buffer después de usarlo
    mlx_destroy_image(game->img->mlx, img_buffer);

    return (0);
}