/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyasa <eyasa@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 13:20:14 by muguveli          #+#    #+#             */
/*   Updated: 2024/08/03 15:42:24 by eyasa            ###   ########.fr       */
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
	g_sig = IN_CMD;
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

	i = 0;
	args = minishell->args;
	if (check_direct(minishell, args[i]))
		return (free_args(minishell->args_with_quotes), free_args(args),
			FAILURE);
	if (args[0][0] == NULL)
		return (reset_fd(minishell), free_args(args),
			free_args(minishell->args_with_quotes), SUCCESS);
	cmd = ft_calloc(dlist_size(minishell->tokens) + 1, sizeof(char *));
	if (!cmd)
		return (FAILURE);
	remove_quotes(args);
	init_cmd(args, cmd);
	ft_all_lower(&cmd[i]);
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
