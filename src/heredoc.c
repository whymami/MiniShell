/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyasa <eyasa@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 14:48:02 by eyasa             #+#    #+#             */
/*   Updated: 2024/07/16 19:42:44 by eyasa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	find_heredoc(t_minishell *mini)
{
	char	*line;
	int		i;

	line = ft_strdup(mini->line);
	i = 0;
	if (!line)
		return (0);
	while (line[i])
	{
		if (line[i] == '<' && line[i + 1] == '<' && line[i + 2] == '<')
			return (free(line), 0);
		if (line[i] == '<' && line[i + 1] == '<' && line[i + 2] != '<')
			if (!check_quote(line, i))
				return (free(line), 1);
		i++;
	}
	return (free(line), 0);
}

static char	*get_delimiter(t_minishell *mini)
{
	char	*line;
	char	*delimiter;
	int		i;
	int		j;

	i = 0;
	line = ft_strdup(mini->line);
	if (!line)
		return (NULL);
	while (line[i] && line[i] != '<')
		i++;
	i += 2;
	while (line[i] && ((line[i] >= 9 && line[i] <= 13) || line[i] == ' '))
		i++;
	if (line[i] == '\0')
		return (free(line), NULL);
	j = i;
	while (line[j] && !((line[j] >= 9 && line[j] <= 13) || line[j] == ' '))
		j++;
	delimiter = ft_substr(line, i, j - i);
	return (free(line), delimiter);
}

void	set_hrd_cmd(t_minishell *mini)
{
	int		i;
	char	*cmd;
	char	*line;

	i = 0;
	line = ft_strdup(mini->line);
	if (!line)
		return ;
	while (line[i] && line[i] != '<')
		i++;
	cmd = malloc(sizeof(char) * i + 1);
	ft_strlcpy(cmd, line, i);
	free(line);
	cmd = ft_strtrim(cmd, " ");
	if (!mini->hrd_cmd)
		mini->hrd_cmd = dlist_new(cmd);
	else
		dlist_add_back(&mini->hrd_cmd, dlist_new(cmd));
}

int	heredoc(t_minishell *mini)
{
	char	*line;
	char	*delimiter;

	line = NULL;
	delimiter = NULL;
	if (!find_heredoc(mini))
		return (0);
	delimiter = get_delimiter(mini);
	if (!delimiter)
		return (ft_printf("%s%s `newline'\n", ERR_TITLE, SYNTAX_ERR), 1);
			// komut yoksa yani " << eof" gibi bir durumda executor komut yok hatası bastırmamalı.
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0
			&& ft_strlen(line) == ft_strlen(delimiter))
		{
			set_hrd_cmd(mini);
			return (free(delimiter), free(line), 0);
		}
		add_history(line);
		free(line);
	}
	free(delimiter);
	return (0);
}
