/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btanir <btanir@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 15:34:45 by btanir            #+#    #+#             */
/*   Updated: 2024/07/06 15:36:06 by btanir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	real_pipe_count(t_minishell *minishell)
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

static void	lexer_split_pipe(t_minishell *minishell, int *i, int *pipe_count,
		int *last_pipe)
{
	char	*temp_str;

	if ((minishell->line[*i] == '|' || minishell->line[*i] == '\0')
		&& quote_handler(minishell, *i, 1) == 0)
	{
		temp_str = ft_substr(minishell->line, *last_pipe, (*i) - (*last_pipe));
		minishell->tokens[*pipe_count] = ft_strtrim(temp_str, " ");
		(*pipe_count)++;
		*last_pipe = *i + 1;
	}
}

void	lexer(t_minishell *minishell)
{
	int	i;
	int	pipe_count;
	int	last_pipe;

	i = -1;
	pipe_count = 0;
	last_pipe = 0;
	real_pipe_count(minishell);
	minishell->tokens = malloc(sizeof(char *) * (minishell->pipe_count + 1));
	while (minishell->line[++i])
		lexer_split_pipe(minishell, &i, &pipe_count, &last_pipe);
	lexer_split_pipe(minishell, &i, &pipe_count, &last_pipe);
	minishell->tokens[pipe_count] = NULL;
	pipe_count = 0;
	while (minishell->tokens[pipe_count])
	{
		printf("%s\n", minishell->tokens[pipe_count]);
		pipe_count++;
	}
}
