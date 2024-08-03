/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btanir <btanir@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 00:03:44 by eyasa             #+#    #+#             */
/*   Updated: 2024/08/03 18:30:56 by btanir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	process_delimiters(t_minishell *mini, char ***delimiters)
{
	char	***args;
	int		i;

	args = mini->args;
	i = -1;
	while (++i <= mini->pipe_count)
	{
		(delimiters)[i] = get_delimiters(mini, args[i]);
		if (!(delimiters)[i] && mini->hrd_count > 0)
		{
			while (--i >= 0)
				free_split((delimiters)[i]);
			free(delimiters);
			return (0);
		}
	}
	return (1);
}

int	heredoc_loop(t_minishell *mini, char **delimiters, int *j, int *fd)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (g_sig == 1)
		{
			if (mini->pipe_count == 0)
				reset_fd(mini);
			return (free(line), FAILURE);
		}
		if (!line || ft_strcmp(line, delimiters[(*j)]) == 0)
		{
			free(line);
			(*j)++;
			break ;
		}
		ft_putstr_fd(line, fd[1]);
		ft_putchar_fd('\n', fd[1]);
		free(line);
	}
	return (SUCCESS);
}

static int	read_heredoc(char **delimiters, t_minishell *mini, int i)
{
	int	j;
	int	fd[2];

	if (pipe(fd) == -1)
		return (FAILURE);
	if (mini->pipe_count == 0)
		dup_fd(mini);
	g_sig = 2;
	j = 0;
	while (delimiters[j] && g_sig == 2)
		if (heredoc_loop(mini, delimiters, &j, fd))
			return (FAILURE);
	close(fd[1]);
	if (mini->pipe_count != 0)
		mini->heredoc_fd[i] = fd[0];
	else
	{
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
	}
	return (SUCCESS);
}

int	delimiter(t_minishell *mini, char ***args)
{
	char	***delimiters;
	int		i;

	mini->heredoc_fd = (int *)malloc(sizeof(int) * (mini->pipe_count + 1));
	if (!mini->heredoc_fd)
		return (FAILURE);
	delimiters = (char ***)malloc(sizeof(char **) * (mini->pipe_count + 1));
	if (!delimiters)
		return (free(mini->heredoc_fd), FAILURE);
	if (!process_delimiters(mini, delimiters) || !delimiters)
		return (printf("%s%s `newline'\n", ERR_TITLE, SYNTAX_ERR),
			mini->exit_code = 2, FAILURE);
	i = -1;
	while (++i <= mini->pipe_count)
	{
		mini->heredoc_fd[i] = -1;
		if (delimiters[i] && delimiters[i][0])
			if (read_heredoc(delimiters[i], mini, i))
				return (free_split(delimiters[i]), free(delimiters), FAILURE);
		free_split(delimiters[i]);
		null_heredoc_args(args[i]);
	}
	return (free(delimiters), SUCCESS);
}

int	heredoc(t_minishell *mini)
{
	char	***args;
	int		i;

	args = mini->args;
	i = -1;
	if (!args)
		return (0);
	while (args[++i])
	{
		if (check_heredoc_syntax_errors(args[i]))
		{
			mini->exit_code = 2;
			return (FAILURE);
		}
	}
	if (mini->hrd_count == 0)
		return (SUCCESS);
	if (delimiter(mini, args) == FAILURE)
		return (FAILURE);
	if (mini->pipe_count == 0)
		free(mini->heredoc_fd);
	return (SUCCESS);
}
