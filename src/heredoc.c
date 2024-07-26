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

static char	**get_delimiters(t_minishell *mini, char **args)
{
	char	**delimiters;
	int		i;
	int		j;

	j = 0;
	delimiters = (char **)malloc(sizeof(char *) * (mini->hrd_count + 1));
	if (!delimiters)
		return (NULL);
	i = -1;
	while (args[++i])
	{
		if (ft_strncmp(args[i], "<<", 2) == 0 && args[i + 1])
		{
			delimiters[j] = ft_strdup(args[i + 1]);
			if (!delimiters[j])
			{
				while (--j >= 0)
					free(delimiters[j]);
				return (free(delimiters), NULL);
			}
			j++;
		}
	}
	delimiters[j] = NULL;
	return (delimiters);
}

void	null_heredoc_args(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		if (ft_strncmp(args[i], "<<", 2) == 0 && args[i + 1])
		{
			free(args[i]);
			args[i] = NULL;
			free(args[i + 1]);
			args[i + 1] = NULL;
			i += 2;
		}
		else
			i++;
	}
}

int	heredoc(t_minishell *mini)
{
	char *line;
	char **delimiters;
	char ***args;
	int i, j;

	i = 0;
	args = mini->args;
	line = NULL;
	if (!args)
		return (0);

	delimiters = NULL;
	while (i <= mini->pipe_count)
	{
		char **temp_delimiters = get_delimiters(mini, args[i]);
		if (temp_delimiters)
		{
			if (!delimiters)
				delimiters = temp_delimiters;
			else
			{
				int existing_count = 0;
				while (delimiters[existing_count])
					existing_count++;

				int new_count = 0;
				while (temp_delimiters[new_count])
					new_count++;

				delimiters = (char **)my_realloc(delimiters, sizeof(char *)
						* (existing_count + new_count + 1));
				if (!delimiters)
					return (0);
				j = -1;
				while (++j < new_count)
					delimiters[existing_count + j] = temp_delimiters[j];
				delimiters[existing_count + new_count] = NULL;

				free(temp_delimiters);
			}
		}
		i++;
	}
	if (!delimiters || !delimiters[0])
		return (ft_printf("%s%s `newline'\n", ERR_TITLE, SYNTAX_ERR), 1);
	j = 0;
	while (delimiters[j])
	{
		while (1)
		{
			line = readline("> ");
			if (!line)
				break ;
			if (ft_strcmp(line, delimiters[j]) == 0)
			{
				free(delimiters[j]);
				j++;
				free(line);
				break ;
			}
			free(line);
		}

		if (!line)
			break ;
	}
	while (delimiters[j])
	{
		free(delimiters[j]);
		j++;
	}
	free(delimiters);
	i = -1;
	while (++i <= mini->pipe_count)
		null_heredoc_args(args[i]);
	return (0);
}
