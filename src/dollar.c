/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btanir <btanir@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 16:25:44 by eyasa             #+#    #+#             */
/*   Updated: 2024/07/29 20:39:56 by muguveli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	replace_dollar(t_minishell *mini, int *i, char **result)
{
	char	*tmp;
	char	*str;

	str = mini->line;
	if (str[*i] == '$' && str[(*i) + 1] && str[(*i) + 1] == '?')
		return (get_ext_code(i, mini, result));
	if (str[*i] == '$' && str[(*i) + 1] && str[(*i) + 1] != '$')
		return (get_env(i, mini, &str, result));
	tmp = *result;
	*result = ft_strjoin_char(tmp, str[(*i)++]);
}

static int	empty_dollar(char *str)
{
	int	i;
	int sign;
	i = 0;
	sign = 0;
	while ((*str)[i])
	{
		if ((*str)[i] == '$')
			sign = 1;
		i++;
	}
	if (sign == 0)
		return (1);
	i = 0;
	while ((*str)[i])
	{
		if ((*str)[i] == '$')
		{
			if ((!ft_isalnum(str[i + 1]) && (str[i + 1] != '?') && (str[i
						+ 1] != '$')))
				return (1);
		}
		i++;
	}
	return (0);
}

void	dollar(t_minishell *mini, int i)
{
	char	*result;
	char	*tmp;
	char	quote;

	quote = 0;
	if (empty_dollar(mini->line))
		return ;
	result = ft_strdup("");
	while (mini->line[i])
	{
		if (quote == 0 && (mini->line[i] == '\'' || mini->line[i] == '\"'))
			quote = mini->line[i];
		else if (quote != 0 && quote == mini->line[i])
			quote = 0;
		if (quote == '\'' || (quote == 0 && mini->line[i] == '\''))
		{
			tmp = result;
			result = ft_strjoin_char(tmp, mini->line[i++]);
		}
		else
			replace_dollar(mini, &i, &result);
	}
	free(mini->line);
	mini->line = result;
}
