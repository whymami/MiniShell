/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_func1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muguveli <muguveli@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 13:55:24 by muguveli          #+#    #+#             */
/*   Updated: 2023/12/27 16:05:42 by muguveli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unistd.h"

int	ft_putchar(char c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_putstr(char *c)
{
	int	i;

	i = 0;
	if (!c)
	{
		i = ft_putstr("(null)");
		return (6);
	}
	while (c[i])
	{
		ft_putchar(c[i]);
		i++;
	}
	return (i);
}

int	ft_putnbr(int c)
{
	int	i;

	i = 0;
	if (c == -2147483648)
		i += ft_putstr("-2147483648");
	else if (c < 0)
	{
		i += ft_putchar('-');
		i += ft_putnbr(c * (-1));
	}
	else if (c > 9)
	{
		i += ft_putnbr(c / 10);
		i += ft_putnbr(c % 10);
	}
	else if (c <= 9)
	{
		i += ft_putchar(c + 48);
	}
	return (i);
}
