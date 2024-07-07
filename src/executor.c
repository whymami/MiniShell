/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halozdem <halozdem@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 13:20:14 by halozdem          #+#    #+#             */
/*   Updated: 2024/07/07 18:29:07 by halozdem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
 #include <sys/wait.h>

void execute_command(char *cmd,  char **args)
{
	pid_t 	pid;
	int		status = 0;

	if (access(cmd, F_OK) == -1)
	{
		perror("Command not found or not executable.\n");
		return ;
	}
	pid = fork();
	if (pid == 0)
	{
		if (execve(cmd, args, NULL) == -1)
		{
			perror("execve");
			exit(EXIT_FAILURE);
		}
	}
	else if (pid < 0)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else
		waitpid(pid, &status, 0);
}
