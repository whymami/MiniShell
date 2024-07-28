/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muguveli <muguveli@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 14:07:53 by muguveli          #+#    #+#             */
/*   Updated: 2024/07/28 15:24:55 by muguveli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	remove_quotes_helper(char **tmp2, char **tmp, char **new_tmp)
{
	int	k;
	int	quote;

	k = -1;
	quote = 0;
	while ((*tmp2)[++k])
	{
		if (quote == 0 && ((*tmp2)[k] == '\'' || (*tmp2)[k] == '\"'))
			quote = (*tmp2)[k];
		else if (quote != 0 && quote == (*tmp2)[k])
			quote = 0;
		else
		{
			*new_tmp = ft_strjoin_char(*tmp, (*tmp2)[k]);
			if (!(*new_tmp))
				return ;
			*tmp = *new_tmp;
		}
	}
}

void	remove_quotes(char ***args)
{
	int		i;
	int		j;
	char	*tmp;
	char	*tmp2;
	char	*new_tmp;

	i = -1;
	while (args[++i])
	{
		j = -1;
		while (args[i][++j])
		{
			tmp = ft_strdup("");
			if (!tmp)
				return ;
			tmp2 = args[i][j];
			remove_quotes_helper(&tmp2, &tmp, &new_tmp);
			args[i][j] = tmp;
			free(tmp2);
		}
	}
}
