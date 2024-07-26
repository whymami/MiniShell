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

static void	rdirect_out(char *file, int append)
{
	int	fd;

    if (append)
    {
        fd = open(file, O_CREAT | O_WRONLY | O_APPEND, 0644); // if'e süslü parantez koymamın sebebi warning vermesi ft_rdirectte silmeyin
    }
    else
    {
        fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    }
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

static void	rdirect_in(char *file)
{
	int	fd;

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

static int	ft_rdirect(t_minishell *mini, char **args)
{
	int		j;
	char	*file;

	j = 0;
	if (mini->g_fd.change == 0)
	{
		mini->g_fd.std_in = dup(0);
		mini->g_fd.std_out = dup(1);
		mini->g_fd.change = 1;
	}
	while (args[j])
	{
		if ((ft_strcmp(args[j], ">") == 0 && args[j + 1]) || (ft_strcmp(args[j], ">>") == 0 && args[j + 1]))
		{
			file = args[j + 1];
            if (ft_strcmp(args[j], ">") == 0)
                rdirect_out(file, 0);
            else
                rdirect_out(file, 1);
			args[j] = NULL;
			args[j + 1] = NULL;
			j += 2;
		}
		else if (ft_strcmp(args[j], "<") == 0 && args[j + 1])
		{
			file = args[j + 1];
			rdirect_in(file);
			args[j] = NULL;
			args[j + 1] = NULL;
			j += 2;
		}
		else
			j++;
	}
	return (0);
}

void replace_arg(char **args)
{
    char *input;
    int len;
    char *buffer;
    int i;
    int j;

    input = *args;
    len = strlen(input);
    buffer = (char *)malloc((len * 2) + 1);
    if (!buffer)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    i = 0;
    j = 0;
    while (i < len)
    {
        if ((input[i] == '>' || input[i] == '<') && check_quote(input, i) == 0)
        {
            if (i > 0 && input[i - 1] != ' ')
                buffer[j++] = ' ';
            if (input[i] == '>' && input[i + 1] == '>')
            {
                buffer[j++] = '>';
                buffer[j++] = '>';
                i += 2;
            }
            else if (input[i] == '<' && input[i + 1] == '<')
            {
                buffer[j++] = '<';
                buffer[j++] = '<';
                i += 2;
            }
            else
            {
                buffer[j++] = input[i++];
            }
            if (i < len && input[i] != ' ')
                buffer[j++] = ' ';
        }
        else
        {
            buffer[j++] = input[i++];
        }
    }
    buffer[j] = '\0';
    free(*args);
    *args = buffer;
}

int	check_direct(t_minishell *mini, char **args)
{
	int	j;

	j = -1;
	while ((args)[++j])
	{
		if (ft_strcmp((args)[j], ">") == 0 || ft_strcmp((args)[j], "<") == 0 || ft_strcmp((args)[j], ">>") == 0)
		{
			if(ft_rdirect(mini, args))
				return (1);
			return (0);
		}
	}
	return (SUCCESS);
}
