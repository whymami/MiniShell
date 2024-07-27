/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muguveli <muguveli@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 20:17:02 by muguveli          #+#    #+#             */
/*   Updated: 2024/07/27 10:14:12 by muguveli         ###   ########.fr       */
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
		if (pipe(minishell->pipe_fd + i * 2) == -1)
			return (perror("Minishell: pipe error"), FAILURE);
	return (SUCCESS);
}

void pipe_fork(t_minishell *minishell, int i, char **cmd, char ***args)
{
    int j = -1;

    if (i != 0)
    {
        if (dup2(minishell->pipe_fd[(i - 1) * 2], STDIN_FILENO) == -1)
        {
            close(minishell->pipe_fd[(i - 1) * 2]);
            perror("Minishell: dup2 error");
            exit(1);
        }
        close(minishell->pipe_fd[(i - 1) * 2]);
    }
    if (i != minishell->pipe_count)
    {
        if (dup2(minishell->pipe_fd[i * 2 + 1], STDOUT_FILENO) == -1)
        {
            close(minishell->pipe_fd[i * 2 + 1]);
            perror("Minishell: dup2 error");
            exit(1);
        }
        close(minishell->pipe_fd[i * 2 + 1]);
    }
    while (++j < minishell->pipe_count * 2)
        close(minishell->pipe_fd[j]);

    if (check_direct(minishell, args[i]))
        exit(1);

    if (execve(find_path(minishell, cmd[i]), args[i], env(minishell)) == -1)
    {
        type_control(args, env(minishell), &i);
        ft_putstr_fd(" command not found\n", 2);
        exit(127);
    }
}

int	close_fd(t_minishell *minishell)
{
	int	i;

	i = -1;
	while (++i < minishell->pipe_count * 2)
		close(minishell->pipe_fd[i]);
	i = -1;
	while (++i < minishell->pipe_count + 1)
	{
		waitpid(minishell->pid[i], &minishell->exit_code, 0);
		minishell->exit_code = WEXITSTATUS(minishell->exit_code);
	}
	free(minishell->pipe_fd);
	free(minishell->pid);
	return (SUCCESS);
}

int	ft_pipe(t_minishell *minishell, char **cmd, char ***args)
{
	int	i;

	i = -1;
	if (create_pipe(minishell) == FAILURE)
		return (FAILURE);
	while (++i < minishell->pipe_count + 1)
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
	int		a;
	int		b;

	args = minishell->args;
	cmd = ft_calloc(1, sizeof(char *) * (dlist_size(minishell->tokens) + 1));
	remove_quotes(args);
	a = 0;
	b = 0;
	while (args[a]) // utilse at
	{
		if (args[a][0])
		{
			cmd[b] = args[a][0];
			b++;
		}
		a++;
	}
	if (ft_pipe(minishell, cmd, args) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}
