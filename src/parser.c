/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muguveli <muguveli@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 03:46:08 by halozdem          #+#    #+#             */
/*   Updated: 2024/07/28 19:23:54 by muguveli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_quote(char *line, int value_i)
{
	int		i;
	char	quote;

	quote = 0;
	i = -1;
	while (++i < value_i)
	{
		if (quote == 0 && (line[i] == '\'' || line[i] == '\"'))
			quote = line[i];
		else if (quote != 0 && quote == line[i])
			quote = 0;
	}
	return ((int)quote);
}

int	pass_space(char *line, int *i)
{
	while (line[*i])
	{
		if (line[*i] != ' ')
			break ;
		(*i)++;
	}
	if (line[*i] == '\0')
		return (FAILURE);
	return (SUCCESS);
}

static int	check_pipe(char *line, int i)
{
	if (line[i] == '|' && !check_quote(line, i) && line[i + 1]
		&& line[i + 1] == '|')
		return (err_msg(SYNTAX_ERR, " `||\'", NULL), FAILURE);
	else if (line[0] == '|' && !check_quote(line, i))
		return (err_msg(SYNTAX_ERR, " `|\'", NULL), FAILURE);
	return (SUCCESS);
}

static int	check_line(t_minishell *minishell, char *line)
{
	int	i;
	int	pipe;

	i = -1;
	pipe = 0;
	while (line[++i])
	{
		if (check_pipe(line, i))
		{
			minishell->exit_code = 2;
			return (free(line), FAILURE);
		}
		if (pipe != 1 && line[i] == '|' && !check_quote(line, i))
			pipe = 1;
		else if (ft_isprint(line[i]) && line[i] != ' ' && line[i] != '|')
			pipe = 0;
		else if (line[i] == '|')
			break ;
	}
	free(line);
	if (pipe == 1)
		return (err_msg(SYNTAX_ERR, " `|\'", NULL), minishell->exit_code = 2,
			FAILURE);
	return (SUCCESS);
}

int	parser(t_minishell *minishell)
{
	char	*line;
	int		quote;

	line = ft_strtrim(minishell->line, " ");
	quote = check_quote(line, ft_strlen(line));
	if (quote)
		return (free(line), err_msg(SYNTAX_ERR, ft_itoa(quote), NULL), FAILURE);
	if (check_line(minishell, line))
		return (FAILURE);
	return (SUCCESS);
}
