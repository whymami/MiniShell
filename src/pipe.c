/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muguveli <muguveli@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 20:17:02 by muguveli          #+#    #+#             */
/*   Updated: 2024/07/13 14:57:41 by muguveli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int ft_pipe(t_minishell *minishell, char **cmd, char ***args, int *i)
{
	int		pipefd[2];
	pid_t	pid;
	int		status;
	char	**envs;

	*i = 0;
	envs = env(minishell);
	while ((*args)[*i])
	{
		pipe(pipefd);
		pid = fork();
		if (pid == 0)
		{
			if ((*args)[*i + 1])
				dup2(pipefd[1], STD_OUTPUT);
			if (*i != 0)
				dup2(pipefd[0], STD_INPUT);
			close(pipefd[0]);
			close(pipefd[1]);
			if (execve((*cmd)[*i], (*args)[*i], envs) == -1)
			{
				ft_printf("minishell: %s: command not found\n", (*cmd)[*i]);
				exit(1);
			}
		}
		else
		{
			waitpid(pid, &status, 0);
			close(pipefd[1]);
			close(pipefd[0]);
		}
		(*i)++;
	}
	return (SUCCESS);	
}

int	multiple_command(t_minishell *minishell)
{
	char **cmd;
	char ***args;
	int i;

	if (cpy_arg(minishell, &cmd, &args))
		return (FAILURE);
	if (check_bultin(minishell, cmd, args, &i) == 1) //yukarı unutma
		return (SUCCESS);
	if (ft_pipe(minishell, cmd, args, &i))
		return (FAILURE);
	return (SUCCESS);
}