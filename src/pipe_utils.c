/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btanir <btanir@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 16:18:09 by muguveli          #+#    #+#             */
/*   Updated: 2024/07/29 10:11:22 by btanir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	create_pipe(t_minishell *minishell)
{
	int	i;

	i = -1;
	minishell->pipe_fd = malloc(sizeof(int) * (minishell->pipe_count * 2));
	minishell->pid = malloc(sizeof(int) * (minishell->pipe_count + 1));
	if (!minishell->pipe_fd || !minishell->pid)
		return (perror("Minishell: malloc error"), FAILURE);
	while (++i < minishell->pipe_count)
	{
		if (pipe(minishell->pipe_fd + i * 2) == -1)
			return (perror("Minishell: pipe error"), FAILURE);
	}
	return (SUCCESS);
}

void	handle_pipe_dup(t_minishell *minishell, int i)
{
	int	j;

	j = -1;
	if (i != 0)
	{
		if (dup2(minishell->pipe_fd[(i - 1) * 2], STDIN_FILENO) == -1)
		{
			perror("Minishell: dup2 error (stdin)");
			exit(1);
		}
	}
	if (i != minishell->pipe_count)
	{
		if (dup2(minishell->pipe_fd[i * 2 + 1], STDOUT_FILENO) == -1)
		{
			perror("Minishell: dup2 error (stdout)");
			exit(1);
		}
	}
	while (++j < minishell->pipe_count * 2)
		close(minishell->pipe_fd[j]);
}

void	pipe_fork(t_minishell *minishell, int i, char **cmd, char ***args)
{
	char	*path;

	handle_pipe_dup(minishell, i);
	if (check_direct(minishell, args[i]))
		exit(1);
	if (strcmp(cmd[i], "export") != 0)
	{
		path = find_path(minishell, cmd[i]);
		if (execve(path, args[i], env(minishell)) == -1)
		{
			free(path);
			type_control(minishell, args, env(minishell), &i);
			ft_putstr_fd("minishell: ", STDERR_FILENO);
			ft_putstr_fd(args[i][0], STDERR_FILENO);
			ft_putstr_fd(": command not found\n", STDERR_FILENO);
			exit(127);
		}
		free(path);
	}
	else
	{
		type_control(minishell, args, env(minishell), &i);
		exit(0);
	}
}
