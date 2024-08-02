/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyasa <eyasa@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/08/02 23:20:28 by eyasa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */

#include "../include/minishell.h"

int	check_heredoc_syntax_errors(char **args)
{
	int	i;
	int	len;

	i = 0;
	while (args[i])
	{
		len = ft_strlen(args[i]);
		if (len >= 2 && ft_strncmp(args[i], "<<", 2) == 0)
		{
			if (len > 2)
			{
				err_msg(SYNTAX_ERR, "`<<'", NULL);
				return (1);
			}
			if (args[i + 1] && ft_strncmp(args[i + 1], ">>", 2) == 0)
			{
				err_msg(SYNTAX_ERR, "`>>'", NULL);
				return (1);
			}
			if (args[i + 1] && ft_strncmp(args[i + 1], "<<", 2) == 0)
			{
				err_msg(SYNTAX_ERR, "`<<'", NULL);
				return (1);
			}
		}
		i++;
	}
	return (0);
}

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

static int	read_heredoc(char **delimiters, t_minishell *mini, int i)
{
	char	*line;
	int		j;
	int		fd[2];

	if (pipe(fd) == -1)
		return (FAILURE);
	g_sig = 2;
	j = 0;
	while (delimiters[j] && g_sig == 2)
	{
		while (1)
		{
			line = readline("> ");
			if (g_sig == 1)
				break ;
			if (!line || ft_strcmp(line, delimiters[j]) == 0)
			{
				free(line);
				j++;
				break ;
			}
			ft_putstr_fd(line, fd[1]);
			ft_putchar_fd('\n', fd[1]);
			free(line);
		}
	}
	close(fd[0]);
	mini->heredoc_fd[i] = fd[1];
	printf("heredoc_fd[%d] = %d\n", i, mini->heredoc_fd[i]);
	return (SUCCESS);
}

int	heredoc(t_minishell *mini)
{
	char	***args;
	int		i;

	char ***delimiters;
	delimiters = NULL;
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
	delimiters = (char ***)malloc(sizeof(char **) * (mini->pipe_count + 1));
	if (!delimiters)
		return (0);
	if (!process_delimiters(mini, delimiters) || !delimiters)
		return (ft_printf("%s%s `newline'\n", ERR_TITLE, SYNTAX_ERR),
			mini->exit_code = 2, 1);
	i = 0;
	mini->heredoc_fd = (int *)malloc(sizeof(int) * (mini->pipe_count + 1));
	while (i <= mini->pipe_count)
	{
		mini->heredoc_fd[i] = -1;
		if (delimiters[i] && delimiters[i][0])
			read_heredoc(delimiters[i], mini, i);
		null_heredoc_args(args[i]);
		i++;
	}
	return (SUCCESS);
}
