/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muguveli <muguveli@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 16:13:26 by eyasa             #+#    #+#             */
/*   Updated: 2024/07/14 03:09:34 by muguveli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	echo(char **args)
{
	int	i;

	i = 0;
	if (!args[1] && ft_putchar('\n'))
		return ;
	if (ft_strncmp("-n", args[1], 3) == 0)
	{
		i++;
		while (args[++i])
		{
			ft_printf("%s", args[i]);
			if (args[i + 1])
				ft_putchar(' ');
		}
	}	
	else
	{
		while (args[++i])
		{
			ft_printf("%s", args[i]);
			if (args[i + 1])
				ft_putchar(' ');
		}
		ft_putchar('\n');
	}
}
