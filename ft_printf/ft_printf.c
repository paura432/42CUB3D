/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pramos <pramos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 14:11:10 by pramos            #+#    #+#             */
/*   Updated: 2023/03/21 17:48:03 by pramos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_decider(char const *s, va_list args, int *len)
{
	if (*s == 'c')
		ft_char(va_arg(args, int), len);
	else if (*s == 's')
		ft_string(va_arg(args, char *), len);
	else if (*s == 'p')
	{
		write(1, "0x", 2);
		ft_void(va_arg(args, unsigned long int), "0123456789abcdef", len);
		(*len) += 3;
	}
	else if (*s == 'd')
		ft_float(va_arg(args, int), len);
	else if (*s == 'i')
		ft_int(va_arg(args, int), len);
	else if (*s == 'u')
		ft_unsig(va_arg(args, int), "0123456789", len);
	else if (*s == 'x')
		ft_hexminmay(va_arg(args, int), "0123456789abcdef", len);
	else if (*s == 'X')
		ft_hexminmay(va_arg(args, int), "0123456789ABCDEF", len);
	else if (*s == '%')
		ft_porcen(len);
	else
		s--;
}

int	ft_printf(char const *type, ...)
{
	va_list		args;
	int			len;

	va_start (args, type);
	len = 0;
	while (*type != 0)
	{
		if (*type == '%')
		{
			type++;
			ft_decider(type, args, &len);
			type++;
		}
		else
		{
			write(1, &*type, 1);
			type++;
			len++;
		}
	}
	va_end (args);
	return (len);
}
