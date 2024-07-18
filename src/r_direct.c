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

void	ft_rdirect(t_minishell *minishell, char ***args)
{
	int		fd;
	int		j;
	char	*file;

	(void)minishell;
	j = 0;
	while ((*args)[j])
	{
		if (ft_strncmp((*args)[j], ">", 1) == 0 && (*args)[j + 1])
		{
			file = (*args)[j + 1];
			fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
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
			(*args)[j] = NULL;
			(*args)[j + 1] = NULL;
			j += 2;
		}
		else if (ft_strncmp((*args)[j], "<", 1) == 0 && (*args)[j + 1])
		{
			file = (*args)[j + 1];
			fd = open(file, O_RDONLY);
			if (fd == -1)
			{
				perror("open");
				return ;
			}
			if (dup2(fd, STDIN_FILENO) < 0)
			{
				perror("dup2");
				close(fd);
				return ;
			}
			close(fd);
			(*args)[j] = NULL;
			(*args)[j + 1] = NULL;
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
        else if (ft_strncmp((*args)[j], ">>", 1) == 0)
            ft_printf("cmd : %s\n", (*args)[j]);
	}
	return (FAILURE);
}
