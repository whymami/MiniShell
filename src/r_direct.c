/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_direct.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muguveli <muguveli@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 18:55:19 by muguveli          #+#    #+#             */
/*   Updated: 2024/08/03 02:12:55 by muguveli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_syntax_errors(char **args)
{
	int	i;

	i = -1;
	while (args[++i])
	{
		if ((strcmp(args[i], "<>") == 0) || (strcmp(args[i], "><") == 0))
		{
			err_msg(SYNTAX_ERR, "`newline'", NULL);
			return (1);
		}
		if ((strcmp(args[i], ">") == 0 || strcmp(args[i], "<") == 0
				|| strcmp(args[i], ">>") == 0) && (!args[i + 1] || (args[i + 1]
					&& strlen(args[i + 1]) == 0)))
		{
			err_msg(SYNTAX_ERR, "`newline'", NULL);
			return (1);
		}
		if ((ft_strcmp(args[i], "<<") == 0) && (!args[i + 1] || (args[i + 1]
					&& strlen(args[i + 1]) == 0)))
			return (err_msg(SYNTAX_ERR, "`newline'", NULL), 1);
		if ((ft_strcmp(args[i], ">>>") == 0) || (ft_strcmp(args[i], "<<<") == 0))
			return (err_msg(SYNTAX_ERR, "`>'", NULL), 1);
	}
	return (0);
}

static int	rdirect_out(char *file, int *j, int append)
{
	int		fd;
	char	*clean_file;
	(void)*j;
	clean_file = handle_quotes(file);
	if (append)
		fd = open(clean_file, O_CREAT | O_WRONLY | O_APPEND, 0644);
	else
		fd = open(clean_file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	free(clean_file);
	if (fd == -1)
	{
		perror("minishell");
		return (1);
	}
	if (fd >= 0 && dup2(fd, STDOUT_FILENO) == -1)
		return (perror("dup2"), close(fd), 1);
	return (close(fd), 0);
}

static int	rdirect_in(char *file, int *j)
{
	int		fd;
	char	*clean_file;
	(void)*j;
	clean_file = handle_quotes(file);
	fd = open(clean_file, O_RDONLY);
	free(clean_file);
	if (fd == -1)
	{
		perror("minishell");
		return (1);
	}
	if (fd >= 0 && dup2(fd, STDIN_FILENO) == -1)
		return (perror("minishell"), close(fd), 1);
	return (close(fd), 0);
}

int	find_exec(t_minishell *mini, char **args, int *j, int *i, char **file)
{
	(void)mini;
	if ((ft_strcmp(args[(*j)], ">") == 0 && args[(*j) + 1])
		|| (ft_strcmp(args[(*j)], ">>") == 0 && args[(*j) + 1]))
	{
		*file = args[(*j) + 1];
		if (ft_strcmp(args[(*j)], ">") == 0)
		{
			if (rdirect_out(*file, j, 0))
				return (FAILURE);
		}
		else if (rdirect_out(*file, j, 1))
			return (FAILURE);
		free_n_null(args, j);
	}
	else if (ft_strcmp(args[(*j)], "<") == 0 && args[(*j) + 1])
	{
		*file = args[(*j) + 1];
		if (rdirect_in(*file, j))
			return (FAILURE);
		free_n_null(args, j);
	}
	else
	{
		args[(*i)++] = args[(*j)++];
	}
	return (SUCCESS);
}

static int	ft_rdirect(t_minishell *mini, char **args)
{
	int		j;
	char	*file;
	int		i;

	j = 0;
	i = 0;
	dup_fd(mini);
	while (args[j])
	{
		if (find_exec(mini, args, &j, &i, &file))
			return (FAILURE);
	}
	args[i] = NULL;
	return (SUCCESS);
}

int	check_direct(t_minishell *mini, char **args)
{
	int	j;

	j = -1;
	// if (check_syntax_errors(args))
	// 	return (mini->exit_code = 2, FAILURE);
	while ((args)[++j])
	{
		if ((!ft_strcmp((args)[j], ">") || !ft_strcmp((args)[j], "<")
				|| !ft_strcmp((args)[j], ">>")))
		{
			if (ft_rdirect(mini, args))
				return (mini->exit_code = 1, FAILURE);
			return (SUCCESS);
		}
	}
	return (SUCCESS);
}
