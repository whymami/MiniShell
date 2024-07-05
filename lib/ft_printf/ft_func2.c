/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_func2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muguveli <muguveli@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 15:33:45 by muguveli          #+#    #+#             */
/*   Updated: 2024/07/05 18:29:05 by muguveli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_printf.h"

int	ft_uns(unsigned int a)
{
	unsigned int	i;

	i = 0;
	if (a <= 57)
		i += ft_putnbr(a);
	else if (a > 57)
	{
		i += ft_uns(a / 10);
		i += ft_uns(a % 10);
	}
	return (i);
}

int	ft_hex(unsigned int h, int b)
{
	return (ft_ptr(h, b));
}

int	ft_ptr(unsigned long h, int b)
{
	int	i;

	i = 0;
	if (h >= 16)
		i += ft_ptr(h / 16, b);
	if ((h % 16) <= 9)
	{
		i += ft_putchar((h % 16) + '0');
	}
	else
	{
		if (b == 0)
			i += ft_putchar((h % 16) + 87);
		else
			i += ft_putchar((h % 16) + 55);
	}
	return (i);
}
