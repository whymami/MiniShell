/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_arg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muguveli <muguveli@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 20:21:21 by muguveli          #+#    #+#             */
/*   Updated: 2024/07/29 20:22:36 by muguveli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	if_should(char **input, char **buffer, int *i, int *j)
{
	if (((*input)[(*i)] == '>' || (*input)[(*i)] == '<')
		&& check_quote((*input), (*i)) == 0)
	{
		if ((*i) > 0 && (*input)[(*i) - 1] != ' ')
			(*buffer)[(*j)++] = ' ';
		if ((*input)[(*i)] == '>' && (*input)[(*i) + 1] == '>')
		{
			(*buffer)[(*j)++] = '>';
			(*buffer)[(*j)++] = '>';
			(*i) += 2;
		}
		else if ((*input)[(*i)] == '<' && (*input)[(*i) + 1] == '<')
		{
			(*buffer)[(*j)++] = '<';
			(*buffer)[(*j)++] = '<';
			(*i) += 2;
		}
		else
			(*buffer)[(*j)++] = (*input)[(*i)++];
		if ((*i) < (int)ft_strlen(*input) && (*input)[(*i)] != ' ')
			(*buffer)[(*j)++] = ' ';
	}
	else
		(*buffer)[(*j)++] = (*input)[(*i)++];
}

void	replace_arg(char **args)
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
	{

		exit(EXIT_FAILURE);
	}
	i = 0;
	j = 0;
	while (i < len)
		if_should(&input, &buffer, &i, &j);
	buffer[j] = '\0';
	free(*args);
	*args = buffer;
}
