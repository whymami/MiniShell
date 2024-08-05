/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btanir <btanir@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 14:57:05 by muguveli          #+#    #+#             */
/*   Updated: 2024/08/05 15:32:18 by btanir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void init_cmd(char ***args, char **cmd)
{
	int a;
	int b;

	a = -1;
	b = 0;
	while (args[++a])
		if (args[a][0])
			cmd[b++] = args[a][0];
}

void reset_fd(t_minishell *minishell)
{
	if (minishell->fd_handler.change)
	{
		dup2(minishell->fd_handler.std_out, STD_OUTPUT);
		dup2(minishell->fd_handler.std_in, STD_INPUT);
		minishell->fd_handler.change = 0;
	}
}

char *ft_all_lower(char *str)
{
	int i;
	char *cmd;

	cmd = ft_strdup(str);
	i = -1;
	while (cmd[++i])
		cmd[i] = ft_tolower(cmd[i]);
	return (cmd);
}
