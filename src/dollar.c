/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muguveli <muguveli@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 16:25:44 by eyasa             #+#    #+#             */
/*   Updated: 2024/07/28 15:52:10 by muguveli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	replace_dollar(t_minishell *mini, char **str, int *i, char **result)
{
	char	*tmp;

	if ((*str)[*i] == '$' && (*str)[(*i) + 1] && (*str)[(*i) + 1] == '?')
		return (get_ext_code(i, mini, result));
	if ((*str)[*i] == '$' && (*str)[(*i) + 1] && (*str)[(*i) + 1] != '$')
		return (get_env(i, mini, str, result));
	tmp = *result;
	*result = ft_strjoin_char(tmp, (*str)[(*i)++]);
}

static int	empty_dollar(char **str)
{
	int	i;

	i = 0;
	while ((*str)[i])
	{
		if ((*str)[i] == '$')
		{
			if ((!ft_isalnum((*str)[i + 1]) && ((*str)[i + 1] != '?')
					&& ((*str)[i + 1] != '$')))
				return (1);
		}
		i++;
	}
	return (0);
}

void	dollar(t_minishell *mini, char **str, int i)
{
	char	*result;
	char	*tmp;
	char	quote;

	quote = 0;
	if (empty_dollar(str))
		return ;
	result = ft_strdup("");
	while ((*str)[i])
	{
		if (quote == 0 && ((*str)[i] == '\'' || (*str)[i] == '\"'))
			quote = (*str)[i];
		else if (quote != 0 && quote == (*str)[i])
			quote = 0;
		if (quote == '\'' || (quote == 0 && (*str)[i] == '\''))
		{
			tmp = result;
			result = ft_strjoin_char(tmp, (*str)[i++]);
		}
		else
			replace_dollar(mini, str, &i, &result);
	}
	free(*str);
	*str = result;
}
