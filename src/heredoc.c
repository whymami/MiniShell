/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btanir <btanir@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 14:48:02 by eyasa             #+#    #+#             */
/*   Updated: 2024/07/27 11:26:05 by btanir           ###   ########.fr       */
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
		if (ft_strcmp(args[i], "<<") == 0 && args[i + 1])
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

void null_heredoc_args(char **args)
{
    int i = 0;
    int j = 0;

    while (args[i])
    {
        if (!ft_strncmp(args[i], "<<", 2) && args[i + 1])
        {
            free(args[i]);
            free(args[i + 1]);
            i += 2;
        }
        else
        {
            args[j] = args[i];
            i++;
            j++;
        }
    }
    args[j] = NULL;
}


int	heredoc(t_minishell *mini)
{
	char	*line;
	char	**delimiters;
	char	***args;
	char	**temp_delimiters;
	int		existing_count;
	int		new_count;

	int i, j;
	i = 0;
	args = mini->args;
	line = NULL;
	if (!args)
		return (0);
	delimiters = NULL;
	while (i <= mini->pipe_count)
	{
		temp_delimiters = get_delimiters(mini, args[i]);
		if (temp_delimiters)
		{
			if (!delimiters)
				delimiters = temp_delimiters;
			else
			{
				existing_count = 0;
				while (delimiters[existing_count])
					existing_count++;
				new_count = 0;
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
	{
		mini->exit_code = 258;
		return (ft_printf("%s%s `newline'\n", ERR_TITLE, SYNTAX_ERR), 1);
	}
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
