/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muguveli <muguveli@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 16:00:18 by muguveli          #+#    #+#             */
/*   Updated: 2024/07/28 16:01:59 by muguveli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**get_delimiters(t_minishell *mini, char **args)
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

void	null_heredoc_args(char **args)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
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

char	**merge_delimiters(char **delimiters, char **temp_delimiters)
{
	int		existing_count;
	int		new_count;
	char	**new_delimiters;
	int		i;

	existing_count = 0;
	new_count = 0;
	while (delimiters && delimiters[existing_count])
		existing_count++;
	while (temp_delimiters && temp_delimiters[new_count])
		new_count++;
	new_delimiters = (char **)my_realloc(delimiters, sizeof(char *)
			* (existing_count + new_count + 1));
	if (!new_delimiters)
		return (NULL);
	i = -1;
	while (++i < new_count)
		new_delimiters[existing_count + i] = temp_delimiters[i];
	new_delimiters[existing_count + new_count] = NULL;
	free(temp_delimiters);
	return (new_delimiters);
}
