/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halozdem <halozdem@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 03:46:08 by halozdem          #+#    #+#             */
/*   Updated: 2024/07/05 03:46:50 by halozdem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	quote_handler(t_minishell *minishell, int pipe_i, int sign)
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
		else if (quote == 0 && '|' == line[i] && line[i + 1] && line[i + 1] == '|')
			return (printf("%s%s `%s`\n", ERR_TITLE, SYNTAX_ERR, "||"),
			EXIT_FAILURE);
	}
	if (quote != 0 && sign == -1)
		return (printf("%s%s `%c`\n", ERR_TITLE, SYNTAX_ERR, quote),
			EXIT_FAILURE);
	return ((int)quote);
}

static void	real_pipe(t_minishell *minishell)
{
	int		i;
	char	*line;

	i = -1;
	line = minishell->line;
	if (quote_handler(minishell, strlen(line), -1) == 0)
	{
		while (line[++i])
			if (line[i] == '|')
				quote_handler(minishell, i, 1);
	}
}
void	parser(t_minishell *minishell)
{
	char	*line;

	line = minishell->line;
	if ((*line == '|' && *(line + 1) && *(line + 1) == '|') && printf("%s%s `%s`\n", ERR_TITLE, SYNTAX_ERR, "||"))
		return;
	else if (*line == '|' && printf("%s%s `%c`\n", ERR_TITLE, SYNTAX_ERR, '|'))
		return;
	real_pipe(minishell);	// ilk önce real pipeın indeksini bulup orasını linedan çıkartırız

}