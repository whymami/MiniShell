/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyasa <eyasa@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 16:18:09 by muguveli          #+#    #+#             */
/*   Updated: 2024/08/03 13:37:36 by eyasa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int create_pipe(t_minishell *minishell)
{
    int i;

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

void	pipe_fork(t_minishell *minishell, int i, char **cmd, char ***args)
{
	handle_pipe_dup(minishell, i);
	if (check_direct(minishell, args[i]))
		exit(1);
	if (check_builtin(minishell, cmd, args, &i) == 1)
		exit(0);
	if (strcmp(cmd[i], "export") != 0)
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
	else
	{
		type_control(minishell, args, env(minishell), &i);
		exit(0);
	}
}
