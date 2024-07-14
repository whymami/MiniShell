/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muguveli <muguveli@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 20:17:02 by muguveli          #+#    #+#             */
/*   Updated: 2024/07/14 18:33:15 by muguveli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	create_pipe(t_minishell *minishell)
{
	int	i;

	minishell->pipe_fd = malloc(sizeof(int) * (minishell->pipe_count * 2));
	minishell->pid = malloc(sizeof(int) * (minishell->pipe_count + 1));
	if (!minishell->pipe_fd || !minishell->pid)
		return (perror("Minishell: malloc error"), FAILURE);
	for (i = 0; i < minishell->pipe_count; i++)
	{
		if (pipe(minishell->pipe_fd + i * 2) == -1)
			return (perror("Minishell: pipe error"), FAILURE);
	}
	return (SUCCESS);
}

void	pipe_fork(t_minishell *minishell, int i, char **cmd, char ***args)
{
	if (i != 0)
	{
		dup2(minishell->pipe_fd[(i - 1) * 2], STDIN_FILENO);
		close(minishell->pipe_fd[(i - 1) * 2]);
	}
	if (i != minishell->pipe_count)
	{
		dup2(minishell->pipe_fd[i * 2 + 1], STDOUT_FILENO);
		close(minishell->pipe_fd[i * 2 + 1]);
	}
	for (int j = 0; j < minishell->pipe_count * 2; j++)
	{
		close(minishell->pipe_fd[j]);
	}
	if (execve(find_path(minishell, cmd[i]), args[i], env(minishell)) == -1)
	{
		perror("Minishell: execve error");
		exit(1);
	}
}

int	close_fd(t_minishell *minishell)
{
	int	i;
	int	status;

	for (i = 0; i < minishell->pipe_count * 2; i++)
	{
		close(minishell->pipe_fd[i]);
	}
	for (i = 0; i < minishell->pipe_count + 1; i++)
	{
		waitpid(minishell->pid[i], &status, 0);
	}
	free(minishell->pipe_fd);
	free(minishell->pid);
	return (SUCCESS);
}

int	ft_pipe(t_minishell *minishell, char **cmd, char ***args)
{
	int	i;

	if (create_pipe(minishell) == FAILURE)
		return (FAILURE);
	for (i = 0; i < minishell->pipe_count + 1; i++)
	{
		minishell->pid[i] = fork();
		if (minishell->pid[i] == -1)
			return (perror("Minishell: fork error"), FAILURE);
		else if (minishell->pid[i] == 0)
			pipe_fork(minishell, i, cmd, args);
	}
	return (close_fd(minishell));
}

int	multiple_command(t_minishell *minishell)
{
	char	**cmd;
	char	***args;

	if (cpy_arg(minishell, &cmd, &args) == FAILURE)
		return (FAILURE);
	if (ft_pipe(minishell, cmd, args) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

