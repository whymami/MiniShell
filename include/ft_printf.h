/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muguveli <muguveli@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 15:34:51 by muguveli          #+#    #+#             */
/*   Updated: 2023/12/27 15:38:03 by muguveli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

int	ft_putchar(char c);
int	ft_putstr(char *c);
int	ft_putnbr(int c);
int	ft_uns(unsigned int a);
int	ft_printf(const char *str, ...);
int	ft_hex(unsigned int h, int b);
int	ft_ptr(unsigned long h, int b);

#endif