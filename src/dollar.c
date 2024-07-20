/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btanir <btanir@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 16:25:44 by eyasa             #+#    #+#             */
/*   Updated: 2024/07/20 18:54:15 by btanir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*ft_strjoin_char(char *s1, char c)
{
	char	*result;
	int		len;

	len = ft_strlen(s1);
	result = malloc(len + 2);
	if (!result)
		return (NULL);
	ft_strlcpy(result, s1, len + 1);
	result[len] = c;
	result[len + 1] = '\0';
	return (result);
}

void	replace_dollar(t_minishell *mini, char **str, int *i, char **result)
{
	int		start;
	char	*var;
	t_dlist	*value;
	char	*tmp;

	if ((*str)[*i] == '$')
	{
		start = ++(*i);
		while ((*str)[*i] && ft_isalnum((*str)[*i]))
			(*i)++;
		var = ft_substr(*str, start, (*i) - start);
		value = search_env(mini, var);
		if (!value)
			return ;
		tmp = get_value(value->data);
		*result = ft_strjoin(*result, tmp);
		free(tmp);
		free(var);
	}
	else
	{
		tmp = *result;
		*result = ft_strjoin_char(tmp, (*str)[(*i)++]);
		free(tmp);
	}
}

int	empty_dollar(char **str)
{
	int	i;

	i = 0;
	while ((*str)[i])
	{
		if (((*str)[i] == '$' && (((*str)[i + 1] == '\0')
					|| !ft_isalnum((*str)[i + 1]))))
			return (1);
		i++;
	}
	return (0);
}

void	dollar(t_minishell *mini, char **str)
{
	char	*result;
	char	*tmp;
	int		i;
	char	quote;

	quote = 0;
	if (empty_dollar(str))
		return ;
	result = ft_strdup("");
	i = 0;
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
			free(tmp);
		}
		else
			replace_dollar(mini, str, &i, &result);
	}
	free(*str);
	*str = result;
}
