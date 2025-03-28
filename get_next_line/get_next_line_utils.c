/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pramos <pramos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 12:45:22 by pramos            #+#    #+#             */
/*   Updated: 2023/02/23 13:59:58 by pramos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr_gnl(char *str, int c)
{
	while (*str != (char)c && *str != 0)
		str++;
	if (*str == (char)c)
		return ((char *)str);
	else
		return (0);
}

size_t	ft_strlen_gnl(char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

char	*ft_strdup_gnl(char *s1)
{
	char	*result;
	int		i;

	i = ft_strlen_gnl(s1);
	result = (char *)malloc((i + 1) * sizeof(char));
	if (!result)
		return (0);
	i = 0;
	while (s1[i])
	{
		result[i] = s1[i];
		i++;
	}
	result[i] = 0;
	return (result);
}

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	str = malloc((ft_strlen_gnl(s1) + ft_strlen_gnl(s2) + 1) * sizeof(char));
	if (!str)
		return (0);
	if (s1)
	{
		while (s1[i] != '\0')
		{
			str[i] = s1[i];
			i++;
		}
	}
	while (s2[j] != '\0')
	{
		str[i + j] = s2[j];
		j++;
	}
	str[i + j] = '\0';
	free(s1);
	return (str);
}

char	*ft_substr_gnl(char *s, unsigned int start, size_t len)
{
	char	*aux;
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	if (ft_strlen_gnl(s) <= start)
		return (0);
	if (ft_strlen_gnl(&s[start]) < len)
		len = ft_strlen_gnl(&s[start]);
	aux = (char *)malloc(len + 1 * sizeof(char));
	if (!aux)
		return (0);
	while (s[start] != 0 && i < len)
		aux[i++] = s[start++];
	aux[i] = 0;
	return (aux);
}
