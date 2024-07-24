/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muguveli <muguveli@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 14:48:02 by eyasa             #+#    #+#             */
/*   Updated: 2024/07/21 15:45:41 by muguveli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*get_delimiter(t_minishell *mini, char **args)
{
	int i = 0;
	while(args[i])
	{
		if (ft_strncmp(args[i], "<<", 2) == 0)
		{
			if (args[i + 1])
				return (ft_strdup(args[i + 1]));
			else
				return (NULL);
		}
		i++;
	}
	return (NULL);
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

int	heredoc(t_minishell *mini, char **args)
{
	char	*line;
	char	*delimiter;

	line = NULL;
	delimiter = get_delimiter(mini, args);
	if (!delimiter)
		return (ft_printf("%s%s `newline'\n", ERR_TITLE, SYNTAX_ERR), 1);
			// komut yoksa yani " << eof" gibi bir durumda executor komut yok hatası bastırmamalı.
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strcmp(line, delimiter) == 0)
			return (free(delimiter), free(line), 0);
		free(line);
	}
	free(delimiter);
	return (0);
}
