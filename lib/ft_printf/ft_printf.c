/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muguveli <muguveli@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 15:02:03 by muguveli          #+#    #+#             */
/*   Updated: 2024/07/05 18:29:15 by muguveli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_printf.h"
#include "stdarg.h"

int	format(char c, va_list arg)
{
	int	i;

	i = 0;
	if (c == 'c')
		i += ft_putchar(va_arg(arg, int));
	else if (c == 's')
		i += ft_putstr(va_arg(arg, char *));
	else if (c == 'i')
		i += ft_putnbr(va_arg(arg, int));
	else if (c == 'd')
		i += ft_putnbr(va_arg(arg, int));
	else if (c == 'u')
		i += ft_uns(va_arg(arg, unsigned int));
	else if (c == 'x')
		i += ft_hex(va_arg(arg, unsigned int), 0);
	else if (c == 'X')
		i += ft_hex(va_arg(arg, unsigned int), 1);
	else if (c == 'p')
	{
		i += ft_putstr("0x");
		i += ft_ptr(va_arg(arg, unsigned long), 0);
	}
	else
		i += ft_putchar('%');
	return (i);
}

int	ft_printf(const char *str, ...)
{
	int		i;
	int		count;
	va_list	arg;

	va_start(arg, str);
	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '%')
		{
			i++;
			while (str[i] == ' ' && str[i])
				i++;
			count += format(str[i], arg);
			i++;
		}
		else
		{
			count += ft_putchar(str[i]);
			i++;
		}
	}
	va_end(arg);
	return (count);
}
