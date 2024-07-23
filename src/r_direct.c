/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_direct.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyasa <eyasa@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 18:55:19 by muguveli          #+#    #+#             */
/*   Updated: 2024/07/23 17:46:26 by eyasa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_fd		g_fd;

static void	rdirect_out(t_minishell *minishell, char *file)
{
	int	fd;

	(void)minishell;
	fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("open");
		return ;
	}
	if (fd >= 0)
	{
		if (dup2(fd, STDOUT_FILENO) == -1)
		{
			perror("dup2");
			close(fd);
			return ;
		}
	}
	close(fd);
}

static void	rdirect_in(t_minishell *minishell, char *file)
{
	int	fd;

	(void)minishell;
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		perror("open");
		return ;
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror("dup2");
		close(fd);
		return ;
	}
	close(fd);
}

static void	ft_rdirect(t_minishell *minishell, char **args)
{
	int		j;
	char	*file;

	if (g_fd.change == 0)
	{
		g_fd.std_in = dup(0);
		g_fd.std_out = dup(1);
	}
	j = 0;
	while ((args)[j])
	{
		if (ft_strcmp((args)[j], ">") == 0 && (args)[j + 1])
		{
			file = (args)[j + 1];
			rdirect_out(minishell, file);
			(args)[j] = NULL;
			(args)[j + 1] = NULL;
			if ((args)[j + 2])
				j += 2;
		}
		else if (ft_strcmp((args)[j], "<") == 0 && (args)[j + 1])
		{
			file = (args)[j + 1];
			rdirect_in(minishell, file);
			(args)[j] = NULL;
			(args)[j + 1] = NULL;
			if ((args)[j + 2])
				j += 2;
		}
		else
			j++;
	}
}
void replace_arg(char **args) {
    char *input = *args;
    int len = strlen(input);
    char *buffer = (char *)malloc(len * 2 + 1); // Geniş bir buffer ayırdık
    if (!buffer) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    int i = 0, j = 0;

    while (i < len) {
        if ((input[i] == '>' || input[i] == '<') && check_quote(input, i) == 0) {
            // Redirection sembolü bulunursa, boşluk ekle
            if (i > 0 && input[i - 1] != ' ') {
                buffer[j++] = ' ';
            }
            buffer[j++] = input[i++];
            // Eğer redirection sembolü birden fazla karakter değilse ve sonrasındaki karakter boşluk değilse boşluk ekle
            if (i < len && input[i] != ' ') {
                buffer[j++] = ' ';
            }
        } else {
            buffer[j++] = input[i++];
        }
    }
    buffer[j] = '\0';

    // Yeni argümanı eski argüman ile değiştir
    free(*args);
    *args = buffer;
}

int	check_direct(t_minishell *minishell, char **args)
{
	int	j;

	j = -1;
	while ((args)[++j])
	{
		
		if (ft_strcmp((args)[j], ">") == 0 || ft_strcmp((args)[j], "<") == 0)
			ft_rdirect(minishell, args);
		else if (ft_strcmp((args)[j], ">>") == 0)
			ft_printf("cmd : %s\n", (args)[j]);
	}
	return (SUCCESS);
}
