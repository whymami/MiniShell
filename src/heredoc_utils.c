/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyasa <eyasa@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 16:00:18 by muguveli          #+#    #+#             */
/*   Updated: 2024/08/02 23:26:33 by eyasa            ###   ########.fr       */
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
