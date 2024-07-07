/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btanir <btanir@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 15:34:45 by btanir            #+#    #+#             */
/*   Updated: 2024/07/07 18:31:56 by btanir           ###   ########.fr       */
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

static int	lexer_split_pipe(t_minishell *minishell, int *i, int *pipe_count,
		int *last_pipe)
{
	char	*temp_str;
	char	*temp_line;
	char	**args;
	t_token	*token;

	if ((minishell->line[*i] == '|' || minishell->line[*i] == '\0')
		&& quote_handler(minishell, *i, 1) == 0)
	{
		temp_str = ft_substr(minishell->line, *last_pipe, (*i) - (*last_pipe));
		temp_line = ft_strtrim(temp_str, " ");
		free(temp_str);
		token = malloc(sizeof(t_token));
		if (!token)
			return (FAILURE);
		args = ft_split(temp_line, ' ');
		// token->args = 
		free(temp_line);
		// dlist_add_back(&minishell->tokens, dlist_new());
		(*pipe_count)++;
		*last_pipe = *i + 1;
	}
	return(SUCCESS);
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
			minishell->tokens = dlist_new(ft_strtrim(temp_str, " "));
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
	minishell->tokens = malloc(sizeof(t_dlist));
	create_head(minishell, &i, &last_pipe);
	while (minishell->line[++i])
		lexer_split_pipe(minishell, &i, &pipe_count, &last_pipe);
	lexer_split_pipe(minishell, &i, &pipe_count, &last_pipe);
}
