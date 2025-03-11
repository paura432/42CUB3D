/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pau <pau@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 18:19:09 by vini              #+#    #+#             */
/*   Updated: 2025/03/11 20:20:33 by pau              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static int	get_file_info(t_game *game, char **file)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->file_data.lines)
	{
		j = 0;
		while (file[i][j] == ' ' || file[i][j] == '\t' || file[i][j] == '\n')
			j++;
		if (ft_isalpha(file[i][j]))
		{
			copy_info(game, file[i], j);
			i++;
		}
		else if (ft_isdigit(file[i][j]))
		{
			copy_map(game, file, i);
			return (1);
		}
		else
			i++;
	}
	return (0);
}

static int	copy_file(t_game *game, char *file)
{
	game->file_data.lines = count_lines(file);
	if (!game->file_data.lines)
		return (0);
	game->file_data.file_cpy = ft_calloc(game->file_data.lines
			+ 1, sizeof(char *));
	if (!game->file_data.file_cpy)
		return (0);
	game->file_data.fd = open(file, O_RDONLY);
	if (game->file_data.fd < 0)
		return (0);
	fill_copy(game);
	close(game->file_data.fd);
	return (1);
}

static int	check_extension(char *file)
{
	int	fd;

	if (!ft_strnstr(file, ".cub", ft_strlen(file)))
		return (0);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (0);
	close(fd);
	return (1);
}

int	parse(t_game *game, char **argv)
{
	if (!check_extension(argv[1]))
		return (0);
	if (!copy_file(game, argv[1]))
		return (0);
	get_file_info(game, game->file_data.file_cpy);
	return (1);
}
