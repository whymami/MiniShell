/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyasa <eyasa@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 16:13:26 by eyasa             #+#    #+#             */
/*   Updated: 2024/07/09 16:50:53 by eyasa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	echo(char **args)
{
	int	i;

	i = -1;
	if (ft_strncmp("-n", args[0], 3) == 0)
	{
		while (args[1][++i])
			ft_putchar(args[1][i]);
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
