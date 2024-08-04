/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyasa <eyasa@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 16:18:09 by muguveli          #+#    #+#             */
/*   Updated: 2024/08/03 17:29:31 by eyasa            ###   ########.fr       */
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

void	handle_heredoc_dup(t_minishell *minishell, int i)
{
	if (minishell->hrd_count && minishell->heredoc_fd[i] != -1)
	{
		if (dup2(minishell->heredoc_fd[i], STDIN_FILENO) == -1)
		{
			perror("minishell: dup2 error (stdin)");
			exit(1);
		}
		close(minishell->heredoc_fd[i]);
	}
	else if (i != 0)
	{
		if (dup2(minishell->pipe_fd[(i - 1) * 2], STDIN_FILENO) == -1)
		{
			perror("minishell: dup2 error (stdin)");
			exit(1);
		}
	}
}

void	handle_pipe_dup(t_minishell *minishell, int i)
{
	int	j;

	j = -1;
	handle_heredoc_dup(minishell, i);
	if (i != minishell->pipe_count)
	{
		if (dup2(minishell->pipe_fd[i * 2 + 1], STDOUT_FILENO) == -1)
		{
			perror("minishell: dup2 error (stdout)");
			exit(1);
		}
	}
	while (++j < minishell->pipe_count * 2)
		close(minishell->pipe_fd[j]);
}

static void	fork_exec(t_minishell *minishell, char ***args, char **cmd, int i)
{
	minishell->path = find_path(minishell, cmd[i]);
	if (execve(minishell->path, args[i], env(minishell)) == -1)
	{
		type_control(minishell, args, env(minishell), &i);
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(args[i][0], STDERR_FILENO);
		if (minishell->sign)
			free(minishell->path);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
		exit(127);
	}
	if (minishell->sign)
		free(minishell->path);
}

void	pipe_fork(t_minishell *minishell, int i, char **cmd, char ***args)
{
	handle_pipe_dup(minishell, i);
	if (check_direct(minishell, args[i]))
		exit(1);
	if (args[i][0] == NULL)
		exit(0);
	ft_all_lower(&cmd[i]);
	if (check_builtin(minishell, cmd, args, &i) == 1)
		exit(minishell->exit_code);
	fork_exec(minishell, args, cmd, i);
}
