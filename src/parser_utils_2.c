/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pau <pau@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:41:46 by vini              #+#    #+#             */
/*   Updated: 2025/03/10 17:17:10 by pau              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static char	**get_color(char *line, int j)
{
	int		i;
	int		len;
	char	*temp;
	char	*rgb_values;
	char	**rgb_array;

	i = 0;
	len = 0;
	while (line[j] && (line[j] == ' ' || line[j] == '\t'))
		j++;
	i = j;
	while (line[i] && (line[i] != ' ' || line[i] != '\t'))
	{
		len++;
		i++;
	}
	temp = ft_substr(line, j, len);
	rgb_values = ft_strdup_no_nl(temp);
	free(temp);
	rgb_array = ft_split(rgb_values, ',');
	free(rgb_values);
	return (rgb_array);
}

static char	*get_texture(char *line, int j)
{
	int		i;
	int		len;
	char	*temp;
	char	*texture;

	i = 0;
	len = 0;
	while (line[j] && (line[j] == ' ' || line[j] == '\t'))
		j++;
	i = j;
	while (line[i] && (line[i] != ' ' || line[i] != '\t'))
	{
		len++;
		i++;
	}
	temp = ft_substr(line, j, len);
	texture = ft_strdup_no_nl(temp);
	free(temp);
	return (texture);
}

void	copy_colors(t_game *gamet_game, char *line, int j)
{
	if (line[j] == 'F')
	{
		if (gamet_game->tex.f)
			game_error(gamet_game, "Duplicated floor texture\n");
		gamet_game->tex.f = get_color(line, j + 1);
	}
	if (line[j] == 'C')
	{
		if (gamet_game->tex.c)
			game_error(gamet_game, "Duplicated ceiling texture\n");
		gamet_game->tex.c = get_color(line, j + 1);
	}
}

void	copy_textures(t_game *gamet_game, char *line, int j)
{
	if (line[j] == 'N' && line[j + 1] == 'O')
	{
		if (gamet_game->tex.n)
			game_error(gamet_game, "Duplicated north texture\n");
		gamet_game->tex.n = get_texture(line, j + 2);
	}
	if (line[j] == 'S' && line[j + 1] == 'O')
	{
		if (gamet_game->tex.s)
			game_error(gamet_game, "Duplicated south texture\n");
		gamet_game->tex.s = get_texture(line, j + 2);
	}
	if (line[j] == 'E' && line[j + 1] == 'A')
	{
		if (gamet_game->tex.e)
			game_error(gamet_game, "Duplicated east texture\n");
		gamet_game->tex.e = get_texture(line, j + 2);
	}
	if (line[j] == 'W' && line[j + 1] == 'E')
	{
		if (gamet_game->tex.w)
			game_error(gamet_game, "Duplicated west texture\n");
		gamet_game->tex.w = get_texture(line, j + 2);
	}
}

int	count_map_height(char **file, int i)
{
	int	start;
	int	j;

	start = i;
	while (file[i])
	{
		j = 0;
		while (file[i][j] == ' ' || file[i][j] == '\t' || file[i][j] == '\r'
		|| file[i][j] == '\v' || file[i][j] == '\f')
			j++;
		if (file[i][j] != '1')
			break ;
		i++;
	}
	return (i - start);
}
