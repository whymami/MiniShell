/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyasa <eyasa@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 14:57:05 by eyasa             #+#    #+#             */
/*   Updated: 2024/08/03 15:01:02 by eyasa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	init_cmd(char ***args, char **cmd)
{
	int	a;
	int	b;

	a = -1;
	b = 0;
	while (args[++a])
		if (args[a][0])
			cmd[b++] = args[a][0];
}

void	reset_fd(t_minishell *minishell)
{
	if (minishell->g_fd.change)
	{
		dup2(minishell->g_fd.std_out, STD_OUTPUT);
		dup2(minishell->g_fd.std_in, STD_INPUT);
		minishell->g_fd.change = 0;
	}
}
