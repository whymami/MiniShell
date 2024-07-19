/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_direct.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btanir <btanir@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 18:55:19 by muguveli          #+#    #+#             */
/*   Updated: 2024/07/18 18:41:57 by btanir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	rdirect_out(t_minishell *minishell, char *file)
{
	int	fd;
	(void)minishell;
	fd = open(file, O_CREAT | O_WRONLY | O_TRUNC
		, 0644);	
	if (fd == -1)
	{
		perror("open");
		return ;
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("dup2");
		close(fd);
		return ;
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

static void	ft_rdirect(t_minishell *minishell, char ***args)
{
	int		j;
	char	*file;

	j = 0;
	while ((*args)[j])
	{
		if (ft_strncmp((*args)[j], ">", 1) == 0 && (*args)[j + 1])
		{
			file = (*args)[j + 1];
			rdirect_out(minishell, file);
			(*args)[j] = NULL;
			(*args)[j + 1] = NULL;
			if ((*args)[j + 2])
				j += 2;
		}
		else if (ft_strncmp((*args)[j], "<", 1) == 0 && (*args)[j + 1])
		{
			file = (*args)[j + 1];
			rdirect_in(minishell, file);
			(*args)[j] = NULL;
			(*args)[j + 1] = NULL;
			if ((*args)[j + 2])
				j += 2;
		}
		else
			j++;
	}
}

int	check_direct(t_minishell *minishell, char ***args)
{
	int j;

	j = -1;
	while ((*args)[++j])
	{
		if (ft_strncmp((*args)[j], ">", 1) == 0 || ft_strncmp((*args)[j], "<", 1) == 0)
			ft_rdirect(minishell, args);
        else if (ft_strncmp((*args)[j], ">>", 2) == 0)
            ft_printf("cmd : %s\n", (*args)[j]);
	}
	return (SUCCESS);
}
