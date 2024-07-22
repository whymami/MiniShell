/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muguveli <muguveli@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 16:25:44 by eyasa             #+#    #+#             */
/*   Updated: 2024/07/21 15:53:59 by muguveli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

 char	*ft_strjoin_char(char *s1, char c)
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

void	get_ext_code(int *i, t_minishell *mini, char **result)
{
	char	*tmp;
	int		j;
	char	*num;

	j = 0;
	(*i) += 2;
	num = ft_itoa(mini->exit_code);
	while (num[j])
	{
		tmp = *result;
		*result = ft_strjoin_char(tmp, num[j++]);
		free(tmp);
	}
}

void	get_env(int *i, t_minishell *mini, char **str, char **result)
{
	t_dlist	*value;
	int		start;
	char	*tmp;
	char	*var;

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

int is_valid_env_char(char c)
{
    return (ft_isalnum(c) || c == '_');
}

void replace_dollar(t_minishell *mini, char **str, int *i, char **result)
{
    char *tmp;

    if ((*str)[*i] == '$' && (*str)[(*i) + 1] == '?')
        return (get_ext_code(i, mini, result));
    if ((*str)[*i] == '$')
        return (get_env(i, mini, str, result));
    tmp = *result;
    *result = ft_strjoin_char(tmp, (*str)[(*i)++]);
    free(tmp);
}


int	empty_dollar(char **str)
{
	int	i;

	i = 0;
	while ((*str)[i])
	{
		if ((*str)[i] == '$')
		{
			if (((*str)[i + 1] == '\0') || (!ft_isalnum((*str)[i + 1]) &&
                ((*str)[i + 1] != '?' && (*str)[i + 1] != '\'' && (*str)[i + 1] != '\"')))
				return (1);
		}
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
