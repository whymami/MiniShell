/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btanir <btanir@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 15:34:45 by btanir            #+#    #+#             */
/*   Updated: 2024/07/09 21:11:17 by btanir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	create_token(t_minishell *minishell, int *i, int *last_pipe)
{
	char	*temp_str;
	char	*temp_line;
	char	*line;

	line = minishell->line;
	while (1)
	{
		if ((line[*i] == '|' || line[*i] == '\0') && quote_handler(minishell,
				*i, 1) == 0)
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
	create_token(minishell, &i, &last_pipe);
}
