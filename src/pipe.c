/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btanir <btanir@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 20:17:02 by muguveli          #+#    #+#             */
/*   Updated: 2024/07/14 12:47:02 by btanir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int ft_pipe(t_minishell *minishell, char **cmd, char ****args, int *i)
{
    int pipefd[2];
    pid_t pid;
    int status;
    char **envs;
    char *path;
    int in_fd;

    in_fd = 0;
    envs = env(minishell);

    while ((*args)[*i])
    {
        path = find_path(minishell, (*args)[*i][0]);

        // Bir sonraki komut olup olmadığını kontrol et
        if ((*args)[*i + 1])
        {
            if (pipe(pipefd) == -1)
                return (perror("pipe"), FAILURE);
        }

        pid = fork();
        if (pid == -1)
            return (perror("fork"), FAILURE);
        else if (pid == 0)
        {
            // Alt süreçte (child process)

            // Önceki komuttan gelen giriş dosya tanıtıcısını ayarla
            if (in_fd != 0)
            {
                dup2(in_fd, STDIN_FILENO);
                close(in_fd);
            }

            // Eğer bir sonraki komut varsa, çıkışı pipe'a yönlendir
            if ((*args)[*i + 1])
            {
                dup2(pipefd[1], STDOUT_FILENO);
                close(pipefd[1]);
            }

            close(pipefd[0]);

            // Gömülü komutları kontrol et
            if (check_bultin(minishell, cmd, *args, i) == 1)
                exit(0);

            // Komutu çalıştır
            if (execve(path, (*args)[*i], envs) == -1)
            {
                ft_printf("minishell: %s: command not found\n", cmd[*i]);
                exit(1);
            }
        }
        else
        {
            // Ana süreçte (parent process)

            // Çocuk sürecin bitmesini bekle
            waitpid(pid, &status, 0);

            if (in_fd != 0)
                close(in_fd);

            if ((*args)[*i + 1])
                close(pipefd[1]);

            // Giriş dosya tanıtıcısını güncelle
            in_fd = pipefd[0];
        }

        (*i)++;
    }

    return (SUCCESS);
}

int multiple_command(t_minishell *minishell)
{
    char **cmd;
    char ***args;
    int i;

    i = 0;

    if (cpy_arg(minishell, &cmd, &args))
        return (FAILURE);

    if (ft_pipe(minishell, cmd, &args, &i))
        return (FAILURE);

    return (SUCCESS);
}
