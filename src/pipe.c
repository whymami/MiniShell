/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muguveli <muguveli@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 20:17:02 by muguveli          #+#    #+#             */
/*   Updated: 2024/07/27 21:08:49 by muguveli         ###   ########.fr       */
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
		{
			perror("Minishell: pipe error");
			return FAILURE;
		}
	}
	return SUCCESS;
}

void pipe_fork(t_minishell *minishell, int i, char **cmd, char ***args)
{
	int j;
	int k;

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
	for (j = 0; j < minishell->pipe_count * 2; j++)
	{
		close(minishell->pipe_fd[j]);
	}

	if (check_direct(minishell, args[i]))
	{
		exit(1);
	}

	// Komutun "export" olup olmadığını kontrol et
	if (strcmp(cmd[i], "export") != 0)
	{
		if (execve(find_path(minishell, cmd[i]), args[i], env(minishell)) == -1)
		{
			type_control(minishell, args, env(minishell), &i);
			k = 0;
			
			ft_putstr_fd("minishell: ", STDERR_FILENO);
			ft_putstr_fd(args[i][0], STDERR_FILENO);
			ft_putstr_fd(": command not found\n", STDERR_FILENO);
			
			exit(127); 
		}
	}
	else
	{
		type_control(minishell, args, env(minishell), &i);
		exit(0); // "export" komutu için başarıyla çık
	}
}

int close_fd(t_minishell *minishell)
{
	int i;

	for (i = 0; i < minishell->pipe_count * 2; i++)
	{
		close(minishell->pipe_fd[i]);
	}
	for (i = 0; i < minishell->pipe_count + 1; i++)
	{
		waitpid(minishell->pid[i], &minishell->exit_code, 0);
		minishell->exit_code = WEXITSTATUS(minishell->exit_code);
	}
	free(minishell->pipe_fd);
	free(minishell->pid);
	return SUCCESS;
}

int ft_pipe(t_minishell *minishell, char **cmd, char ***args)
{
	int i;

	if (create_pipe(minishell) == FAILURE)
	{
		return FAILURE;
	}
	for (i = 0; i < minishell->pipe_count + 1; i++)
	{
		minishell->pid[i] = fork();
		if (minishell->pid[i] == -1)
		{
			perror("Minishell: fork error");
			return FAILURE;
		}
		else if (minishell->pid[i] == 0)
		{
			pipe_fork(minishell, i, cmd, args);
		}
	}
	return close_fd(minishell);
}

int multiple_command(t_minishell *minishell)
{
	char **cmd;
	char ***args;
	int a, b;

	args = minishell->args;
	cmd = ft_calloc(1, sizeof(char *) * (dlist_size(minishell->tokens) + 1));
	remove_quotes(args);
	a = 0;
	b = 0;
	while (args[a])
	{
		if (args[a][0])
		{
			cmd[b] = args[a][0];
			b++;
		}
		a++;
	}
	if (ft_pipe(minishell, cmd, args) == FAILURE)
	{
		return FAILURE;
	}
	return SUCCESS;
}
