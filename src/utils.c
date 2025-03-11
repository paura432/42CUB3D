/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pau <pau@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 17:10:50 by vini              #+#    #+#             */
/*   Updated: 2025/03/10 17:19:12 by pau              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	print_info(t_game *game)
{
	ft_printf("\n");
	if (game->tex.n)
		ft_printf("north texture is: %s\n", game->tex.n);
	if (game->tex.s)
		ft_printf("south texture is: %s\n", game->tex.s);
	if (game->tex.e)
		ft_printf("east texture is: %s\n", game->tex.e);
	if (game->tex.w)
		ft_printf("west texture is: %s\n", game->tex.w);
	if (game->tex.f)
	{
		ft_printf("\nfloor rgb value is: \n");
		print_array(game->tex.f);
	}
	if (game->tex.c)
	{
		ft_printf("ceiling rgb value is: \n");
		print_array(game->tex.c);
	}
}

void	print_array(char **array)
{
	int	i;

	i = 0;
	ft_printf("\n");
	while (array[i] != NULL)
	{
		ft_printf("%s\n", array[i]);
		i++;
	}
	ft_printf("\n");
}

void	free_info(t_game *game)
{
	if (game->tex.n)
		free(game->tex.n);
	if (game->tex.s)
		free(game->tex.s);
	if (game->tex.e)
		free(game->tex.e);
	if (game->tex.w)
		free(game->tex.w);
	if (game->tex.f)
		free_array(game->tex.f);
	if (game->tex.c)
		free_array(game->tex.c);
}

void	free_array(char **array)
{
	size_t	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	if (array)
	{
		free(array);
		array = NULL;
	}
}

char	*ft_strdup_no_nl(char *str)
{
	int		i;
	char	*duplicate;

	i = 0;
	duplicate = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!duplicate)
		return (NULL);
	while (str[i] != '\0')
	{
		if (str[i] == '\n')
			break ;
		duplicate[i] = str[i];
		i++;
	}
	duplicate[i] = '\0';
	return (duplicate);
}
