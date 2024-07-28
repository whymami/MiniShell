/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muguveli <muguveli@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 19:18:38 by muguveli          #+#    #+#             */
/*   Updated: 2024/07/28 19:19:13 by muguveli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	init_indis(int i[], int size)
{
	int	j;

	j = -1;
	while (++j < size)
		i[j] = 0;
}

static int	ft_count_words(const char *str, char c)
{
	int	i[3];

	init_indis(i, 3);
	while (*str)
	{
		if (*str == '\'' || *str == '\"')
		{
			if (i[2] == 0)
				i[2] = *str;
			else if (i[2] == *str)
				i[2] = 0;
		}
		if (*str != c || i[2])
		{
			if (!i[1] && i[0]++)
				i[1] = 1;
		}
		else
			i[1] = 0;
		str++;
	}
	return (i[0]);
}

static void	update_quote(char c, int *quote)
{
	if (c == '\'' || c == '\"')
	{
		if (*quote == 0)
			*quote = c;
		else if (*quote == c)
			*quote = 0;
	}
}

static int	split_word(const char *s, char c, int *i, int *quote)
{
	int	start;

	while (s[*i] && (s[*i] == c && *quote == 0))
		(*i)++;
	start = *i;
	while (s[*i] && (s[*i] != c || *quote))
	{
		update_quote(s[*i], quote);
		(*i)++;
	}
	return (start);
}

char	**ft_mini_split(const char *s, char c)
{
	int		i[4];
	char	**dest;
	char	*substr;

	init_indis(i, 4);
	dest = (char **)malloc(sizeof(char *) * (ft_count_words(s, c) + 1));
	if (!dest)
		return (NULL);
	while (s[i[0]])
	{
		i[1] = split_word(s, c, &i[0], &i[2]);
		if (i[0] > i[1])
		{
			substr = ft_substr(s, i[1], i[0] - i[1]);
			if (substr)
			{
				replace_arg(&substr);
				dest[i[3]] = substr;
				i[3]++;
			}
		}
	}
	dest[i[3]] = NULL;
	return (dest);
}
