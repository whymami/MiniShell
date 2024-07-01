/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muguveli <muguveli@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 14:37:22 by muguveli          #+#    #+#             */
/*   Updated: 2024/06/13 18:13:55 by muguveli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void find_path(t_minishell *mini, char **cmds)
{
    char **paths = ft_split(mini->env, ':');
    char *cmd_with_slash = ft_strjoin("/", cmds[0]);
    char *path;
    int i = -1;

    while (paths[++i])
    {
        path = ft_strjoin(paths[i], cmd_with_slash);
        if (access(path, F_OK) == 0)
        {
            execute_cmd(path, cmds);
            free(path);
            break;
        }
        free(path);
    }
    free(cmd_with_slash);
    free_split(paths);
}

void pipe_command(t_minishell *mini)
{
    pid_t *pid = malloc(sizeof(pid_t) * mini->pipe->pipe_count);
    int i = 0;
    int status;
    char **command = ft_split(mini->line, '|');
    int fd[2];

    while (i < mini->pipe->pipe_count)
    {
        char **cmds = ft_split(command[i], ' ');

        pipe(fd);
        pid[i] = fork();
        if (pid[i] == 0)
        {
            close(fd[0]);
            dup2(fd[1], STDOUT_FILENO);
            close(fd[1]);
            find_path(mini, cmds);
            exit(0);
        }
        else if (pid[i] < 0)
        {
            perror("Error");
        }
        else
        {
            waitpid(pid[i], &status, 0);
            close(fd[1]);
            dup2(fd[0], STDIN_FILENO);
            close(fd[0]);
        }
        free_split(cmds);
		i++;
    }
    free(pid);
    free_split(command);
}
