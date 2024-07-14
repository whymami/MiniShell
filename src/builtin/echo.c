/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muguveli <muguveli@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 16:13:26 by eyasa             #+#    #+#             */
/*   Updated: 2024/07/13 21:46:56 by muguveli         ###   ########.fr       */
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
		ft_printf("%s", args[2]);
	else
		ft_printf("%s\n", args[1]);
}
