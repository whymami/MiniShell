/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btanir <btanir@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 15:34:45 by btanir            #+#    #+#             */
/*   Updated: 2024/07/06 21:18:30 by btanir           ###   ########.fr       */
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
		dlinked_list_add_back(&minishell->tokenizer,
			dlinked_list_new(ft_strtrim(temp_str, " ")));
		free(temp_str);
		(*pipe_count)++;
		*last_pipe = *i + 1;
	}
}

static void	create_head(t_minishell *minishell, int *i, int *last_pipe)
{
	char	*temp_str;

	while (1)
	{
		(*i)++;
		if ((minishell->line[*i] == '|' || minishell->line[*i] == '\0')
			&& quote_handler(minishell, *i, 1) == 0)
		{
			temp_str = ft_substr(minishell->line, *last_pipe, *i - *last_pipe);
			minishell->tokenizer = dlinked_list_new(ft_strtrim(temp_str, " "));
			free(temp_str);
			*last_pipe = (*i) + 1;
			break ;
		}
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
	minishell->tokenizer = malloc(sizeof(t_dlinked_list));
	create_head(minishell, &i, &last_pipe);
	while (minishell->line[++i])
		lexer_split_pipe(minishell, &i, &pipe_count, &last_pipe);
	lexer_split_pipe(minishell, &i, &pipe_count, &last_pipe);
}
