/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btanir <btanir@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 13:20:14 by muguveli          #+#    #+#             */
/*   Updated: 2024/07/30 18:56:02 by btanir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <sys/wait.h>

int	create_fork(t_minishell *minishell, char **cmd, char ***args, int *i)
{
	pid_t	pid;

	if (ft_strncmp(cmd[*i], "./", 2))
		minishell->path = find_path(minishell, cmd[*i]);
	else
		minishell->path = cmd[*i];
	pid = fork();
	if (pid < 0)
	{
		if (minishell->sign)
			free(minishell->path);
		return (free_args(args), perror("fork"), FAILURE);
	}
	check_pid(&pid, minishell, args, i);
	if (minishell->sign)
		free(minishell->path);
	return (SUCCESS);
}

static int	single_command(t_minishell *minishell)
{
	char	**cmd;
	char	***args;
	int		i;
	int		a;
	int		b;

	a = -1;
	i = 0;
	b = 0;
	args = minishell->args;
	if (check_direct(minishell, args[i]))
		return (free_args(minishell->args_with_quotes), FAILURE);
	cmd = ft_calloc(dlist_size(minishell->tokens) + 1, sizeof(char *));
	if (!cmd)
		return (FAILURE);
	remove_quotes(args);
	while (args[++a])
		if (args[a][0])
			cmd[b++] = args[a][0];
	if (check_builtin(minishell, cmd, args, &i) == 1)
		return (free(cmd), free_args(minishell->args_with_quotes), SUCCESS);
	free_args(minishell->args_with_quotes);
	if (create_fork(minishell, cmd, args, &i))
		return (free(cmd), FAILURE);
	return (free(cmd), (SUCCESS));
}

int	execute_command(t_minishell *minishell)
{
	if (minishell->pipe_count == 0)
		return (single_command(minishell), SUCCESS);
	else
		return (multiple_command(minishell));
	return (FAILURE);
}
