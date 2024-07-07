/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btanir <btanir@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 03:46:08 by halozdem          #+#    #+#             */
/*   Updated: 2024/07/07 17:32:08 by btanir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	quote_handler(t_minishell *minishell, int pipe_i, int sign)
{
	char	*line;
	char	quote;
	int		i;

	line = minishell->line;
	quote = 0;
	i = -1;
	while (++i < pipe_i)
	{
		if (quote == 0 && (line[i] == '\'' || line[i] == '\"'))
			quote = line[i];
		else if (quote != 0 && quote == line[i])
			quote = 0;
		if (quote == 0 && '|' == line[i] && line[i + 1] && line[i + 1] == '|')
			return (ft_printf("%s%s `%s`\n", ERR_TITLE, SYNTAX_ERR, "||"),
				FAILURE);
	}
	if (quote != 0 && sign == -1)
		return (ft_printf("%s%s `%c`\n", ERR_TITLE, SYNTAX_ERR, quote),
			FAILURE);
	return ((int)quote);
}

static int	real_pipe(t_minishell *minishell)
{
	int		i;
	char	*line;

	i = -1;
	line = minishell->line;
	if (quote_handler(minishell, ft_strlen(line), -1) == 0)
	{
		while (line[++i])
			if (line[i] == '|')
				if (quote_handler(minishell, i, 1) != 0)
					return (FAILURE);
	}
	else
		return (FAILURE);
	return (SUCCESS);
	
}
int	parser(t_minishell *minishell)
{
	char *line;

	line = minishell->line;
	
	if ((*line == '|' && *(line + 1) && *(line + 1) == '|')
		&& ft_printf("%s%s `%s`\n", ERR_TITLE, SYNTAX_ERR, "||"))
		return (FAILURE);
	else if (*line == '|' && printf("%s%s `%c`\n", ERR_TITLE, SYNTAX_ERR, '|'))
		return (FAILURE);
	else if (real_pipe(minishell))
		return (FAILURE);
	return (SUCCESS);
	// ilk önce real pipeın indeksini bulup orasını linedan çıkartırız
}