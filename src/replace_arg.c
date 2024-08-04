/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_arg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btanir <btanir@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 20:21:21 by muguveli          #+#    #+#             */
/*   Updated: 2024/08/03 18:49:59 by btanir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	if_should(char **in, char **buf, int *i, int *j)
{
	if (((*in)[(*i)] == '>' || (*in)[(*i)] == '<') && check_quote(*in, *i) == 0)
	{
		if ((*i) > 0 && (*in)[(*i) - 1] != ' ' && (*in)[(*i) - 1] != '>'
			&& (*in)[(*i) - 1] != '<')
			(*buf)[(*j)++] = ' ';
		if ((*in)[(*i)] == '>' && (*in)[(*i) + 1] == '>')
		{
			(*buf)[(*j)++] = '>';
			(*buf)[(*j)++] = '>';
			(*i) += 2;
		}
		else if ((*in)[(*i)] == '<' && (*in)[(*i) + 1] == '<')
		{
			(*buf)[(*j)++] = '<';
			(*buf)[(*j)++] = '<';
			(*i) += 2;
		}
		else
			(*buf)[(*j)++] = (*in)[(*i)++];
		if ((*i) < (int)ft_strlen(*in) && (*in)[(*i)] != ' '
			&& (*in)[(*i)] != '>' && (*in)[(*i)] != '<')
			(*buf)[(*j)++] = ' ';
	}
	else
		(*buf)[(*j)++] = (*in)[(*i)++];
}

int	replace_arg(char **args)
{
	char	*input;
	int		len;
	char	*buffer;
	int		i;
	int		j;

	input = *args;
	len = ft_strlen(input);
	buffer = (char *)malloc((len * 2) + 1);
	if (!buffer)
		return (perror("malloc"), FAILURE);
	i = 0;
	j = 0;
	while (i < len)
		if_should(&input, &buffer, &i, &j);
	buffer[j] = '\0';
	free(*args);
	*args = buffer;
	return (SUCCESS);
}
