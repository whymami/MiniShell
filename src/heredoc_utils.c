/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btanir <btanir@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 16:00:18 by muguveli          #+#    #+#             */
/*   Updated: 2024/08/03 18:49:14 by btanir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_heredoc_syntax_errors(char **args)
{
	int	i;
	int	len;

	if (check_syntax_errors(args))
		return (1);
	i = -1;
	while (args[++i])
	{
		len = ft_strlen(args[i]);
		if (len >= 2 && ft_strncmp(args[i], "<<", 2) == 0)
		{
			if (len > 2)
				return (err_msg(SYNTAX_ERR, "`<<'", NULL), 1);
			if (args[i + 1] && ft_strncmp(args[i + 1], ">>", 2) == 0)
				return (err_msg(SYNTAX_ERR, "`>>'", NULL), 1);
			if (args[i + 1] && ft_strncmp(args[i + 1], "<<", 2) == 0)
				return (err_msg(SYNTAX_ERR, "`<<'", NULL), 1);
		}
	}
	return (0);
}

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
