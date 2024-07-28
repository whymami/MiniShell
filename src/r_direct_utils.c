/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_direct_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muguveli <muguveli@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 20:18:41 by muguveli          #+#    #+#             */
/*   Updated: 2024/07/28 20:41:30 by muguveli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	dup_fd(t_minishell *mini)
{
	if (mini->g_fd.change == 0)
	{
		mini->g_fd.std_in = dup(0);
		mini->g_fd.std_out = dup(1);
		mini->g_fd.change = 1;
	}
}

void	free_n_null(char **args, int *j)
{
	free(args[(*j)]);
	free(args[(*j) + 1]);
	args[(*j)] = NULL;
	args[(*j) + 1] = NULL;
	(*j) += 2;
}

char	*handle_quotes(const char *str)
{
	char	*result;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!str)
		return (NULL);
	result = malloc(strlen(str) + 1);
	if (!result)
		return (NULL);
	while (str[i])
	{
		if (str[i] != '"' && str[i] != '\'')
		{
			result[j++] = str[i];
		}
		i++;
	}
	result[j] = '\0';
	return (result);
}
