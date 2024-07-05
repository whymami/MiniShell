/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muguveli <muguveli@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 00:40:49 by halozdem          #+#    #+#             */
/*   Updated: 2024/07/05 20:06:36 by muguveli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "stdio.h"
#include "stdlib.h"

void	real_pipe_count(t_minishell *minishell)
{
	int		i;
	char	*line;

	i = -1;
	line = minishell->line;
	minishell->pipe_count = 0;
	while (line[++i])
		if (line[i] == '|' && quote_handler(minishell, i, 1) == 0)
			minishell->pipe_count++;
}

void	lexer(t_minishell *minishell)
{
	int	i;
	int	line_len;
	int	pipe_count;
	int	last_pipe;

	i = 0;
	pipe_count = 0;
	last_pipe = 0;
	real_pipe_count(minishell);
	minishell->tokens = malloc(sizeof(char *) * (minishell->pipe_count + 1));
	line_len = ft_strlen(minishell->line);
	while (i < line_len || minishell->line[i] != '\0'
		|| pipe_count <= minishell->pipe_count)
	{
		if ((minishell->line[i] == '|' || minishell->line[i] == '\0')
			&& quote_handler(minishell, i, 1) == 0)
		{
			minishell->tokens[pipe_count++] = ft_substr(minishell->line,
					last_pipe, i - last_pipe);
			last_pipe = i + 1;
		}
		i++;
	}
	pipe_count = 0;
	while (pipe_count <= minishell->pipe_count)
	{
		printf("%s\n", minishell->tokens[pipe_count]);
		pipe_count++;
	}
}

int	main(void)
{
	t_minishell	*minishell;

	minishell = malloc(sizeof(t_minishell));
	while (1)
	{
		minishell->line = readline("minishell> ");
		if (ft_strlen(minishell->line) != 0)
			add_history(minishell->line);
		parser(minishell);
		lexer(minishell);
	}
	return (EXIT_SUCCESS);
}
