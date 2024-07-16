/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_direct.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muguveli <muguveli@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 18:55:19 by muguveli          #+#    #+#             */
/*   Updated: 2024/07/15 21:09:05 by muguveli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_rdirect(t_minishell *minishell, char **cmd, char ***args, int *i)
{
	ft_printf("cmd : %s\n", (*args)[1]);
	ft_printf("cmd : %s\n", (*args)[2]);
	ft_printf("cmd : %s\n", (*args)[3]);
    (void)cmd;
	(void)args;
	(void)minishell;
	(void)i;
}

int	check_direct(t_minishell *minishell, char **cmd, char ***args, int *i)
{
	int j;

	j = -1;
	while ((*args)[++j])
	{
		if (ft_strncmp((*args)[j], ">", 1) == 0 || ft_strncmp((*args)[j], "<", 1) == 0)
			ft_rdirect(minishell, cmd, args, i);
        else if (ft_strncmp((*args)[j], ">>", 1) == 0)
            ft_printf("cmd : %s\n", (*args)[j]);
	}
	return (FAILURE);
}