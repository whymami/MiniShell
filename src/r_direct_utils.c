/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_direct_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btanir <btanir@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 20:18:41 by muguveli          #+#    #+#             */
/*   Updated: 2024/08/04 11:25:09 by btanir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_syntax_errors(char **args)
{
	int	i;

	i = -1;
	while (args[++i])
	{
		if ((ft_strcmp(args[i], "<>") == 0) || (ft_strcmp(args[i], "><") == 0))
			return (err_msg(SYNTAX_ERR, "`newline'", NULL), 1);
		if ((ft_strcmp(args[i], ">") == 0 || ft_strcmp(args[i], "<") == 0
				|| ft_strcmp(args[i], ">>") == 0))
		{
			if ((!args[i + 1] || (args[i + 1] && ft_strlen(args[i + 1]) == 0)))
				return (err_msg(SYNTAX_ERR, "`newline'", NULL), 1);
			if (args[i + 1] && (!ft_strcmp(args[i + 1], "<")
					|| !ft_strcmp(args[i + 1], ">") || !ft_strcmp(args[i + 1],
						">>")))
				return (err_msg(SYNTAX_ERR, "`newline'", NULL), 1);
		}
		if ((ft_strcmp(args[i], "<<") == 0) && (!args[i + 1] || (args[i + 1]
					&& ft_strlen(args[i + 1]) == 0)))
			return (err_msg(SYNTAX_ERR, "`newline'", NULL), 1);
		if ((ft_strcmp(args[i], ">>>") == 0) || (ft_strcmp(args[i],
					"<<<") == 0))
			return (err_msg(SYNTAX_ERR, "`>'", NULL), 1);
	}
	return (0);
}

void	dup_fd(t_minishell *mini)
{
	if (mini->fd_handler.change == 0)
	{
		mini->fd_handler.std_in = dup(0);
		mini->fd_handler.std_out = dup(1);
		mini->fd_handler.change = 1;
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
	result = malloc(ft_strlen(str) + 1);
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
