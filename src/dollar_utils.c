/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyasa <eyasa@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 15:36:16 by muguveli          #+#    #+#             */
/*   Updated: 2024/08/03 14:11:03 by eyasa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_valid_env_char(char c)
{
	return (ft_isalnum(c) || c == '_');
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
	}
	free(num);
}

void	get_env(int *i, t_minishell *mini, char **str, char **result)
{
	t_dlist	*value;
	int		start;
	char	*tmp;
	char	*var;
	char	*new_result;

	start = ++(*i);
	while ((*str)[*i] && ft_isalnum((*str)[*i]))
		(*i)++;
	var = ft_substr(*str, start, (*i) - start);
	value = search_env(mini, var);
	free(var);
	if (!value)
		return ;
	tmp = get_value(value->data);
	new_result = ft_strjoin(*result, tmp);
	free(tmp);
	free(*result);
	*result = new_result;
}
