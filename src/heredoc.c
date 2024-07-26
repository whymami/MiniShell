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

static char	*get_delimiter(char **args)
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

int	heredoc(t_minishell *mini)
{
	char	*line;
	char	*delimiter;
	char	***args;

	args = mini->args;
	line = NULL;
	// printf("args: %s\n", args[1][0]);
	printf("args: %s\n", args[0][0]);
	printf("args: %s\n", args[2][0]);
	delimiter = get_delimiter(args[0]);
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
