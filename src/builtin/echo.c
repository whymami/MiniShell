/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyasa <eyasa@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 16:13:26 by eyasa             #+#    #+#             */
/*   Updated: 2024/07/11 18:16:31 by eyasa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	echo(char **args)
{
	int	i;

	i = -1;
	if (ft_strncmp("-n", args[1], 3) == 0)
	{
		while (args[2][++i])
			ft_putchar(args[2][i]);
	}
	else
	{
		while (args[++i])
		{
			ft_putstr(args[i]);
			ft_putchar(' ');
		}
		ft_putchar('\n');
	}
}
