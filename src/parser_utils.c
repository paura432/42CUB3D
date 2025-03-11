/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pau <pau@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 20:10:59 by vini              #+#    #+#             */
/*   Updated: 2025/03/10 17:21:14 by pau              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	copy_map(t_game *game, char **file, int start)
{
	int	i;

	i = 0;
	game->map_height = count_map_height(file, start);
	game->map = ft_calloc(game->map_height + 1, sizeof(char *));
	if (!game->map)
		return ;
	while (i < game->map_height)
	{
		game->map[i] = ft_strdup(game->file_data.file_cpy[start]);
		i++;
		start++;
	}
}

void	copy_info(t_game *game, char *line, int j)
{
	if (line[j + 1] && ft_isalpha(line[j + 1]))
		copy_textures(game, line, j);
	else
		copy_colors(game, line, j);
}

void	fill_copy(t_game *game)
{
	int		i;
	int		row;
	int		col;
	char	*line;

	i = 0;
	row = 0;
	col = 0;
	line = get_next_line(game->file_data.fd);
	while (line != NULL)
	{
		game->file_data.file_cpy[row]
			= ft_calloc(ft_strlen(line) + 1, sizeof(char));
		if (!game->file_data.file_cpy[row])
			return ;
		while (line[i] != '\0')
			game->file_data.file_cpy[row][col++] = line[i++];
		game->file_data.file_cpy[row++][col] = '\0';
		col = 0;
		i = 0;
		free(line);
		line = get_next_line(game->file_data.fd);
	}
	game->file_data.file_cpy[row] = NULL;
}

int	count_lines(char *file)
{
	int		fd;
	char	*line;
	int		count;

	count = 0;
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (0);
	line = get_next_line(fd);
	while (line != NULL)
	{
		count++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (count);
}
