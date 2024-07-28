/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muguveli <muguveli@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 15:34:45 by btanir            #+#    #+#             */
/*   Updated: 2024/07/28 19:20:44 by muguveli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	count_heredoc(t_minishell *minishell)
{
	int		i;
	char	*line;

	i = 0;
	line = minishell->line;
	minishell->hrd_count = 0;
	while (line[i])
	{
		if (line[i] == '<' && line[i + 1] == '<' && !check_quote(line, i))
		{
			minishell->hrd_count++;
			i++;
		}
		i++;
	}
}

static int	create_token(t_minishell *minishell, int *i, int *last_pipe)
{
	char	*temp_str;
	char	*temp_line;
	char	*line;

	line = ft_strtrim(minishell->line, " ");
	while (1)
	{
		if ((line[*i] == '|' || line[*i] == '\0') && !check_quote(line, *i))
		{
			temp_str = ft_substr(line, *last_pipe, (*i) - (*last_pipe));
			temp_line = ft_strtrim(temp_str, " ");
			free(temp_str);
			if (!minishell->tokens)
				minishell->tokens = dlist_new(temp_line);
			else
				dlist_add_back(&minishell->tokens, dlist_new(temp_line));
			if (line[*i] == '\0')
				break ;
			*last_pipe = *i + 1;
			minishell->pipe_count++;
		}
		(*i)++;
	}
	free(line);
	return (SUCCESS);
}

void	lexer(t_minishell *minishell)
{
	int	i;
	int	last_pipe;

	i = 0;
	last_pipe = 0;
	minishell->pipe_count = 0;
	if (minishell->tokens)
		dlist_clear(&minishell->tokens, &del);
	count_heredoc(minishell);
	create_token(minishell, &i, &last_pipe);
}
