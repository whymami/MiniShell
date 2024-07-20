/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyasa <eyasa@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 19:09:28 by eyasa             #+#    #+#             */
/*   Updated: 2024/07/20 20:05:47 by eyasa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	ft_count_words(char const *str, char c)
{
	int	count;
	int	quote;

	count = 0;
	quote = 0;
	while (*str)
	{
		if (*str != c || quote)
		{
			if (*str == '\'' || *str == '\"')
			{
				if (quote == 0)
					quote = *str;
				else if (quote == *str)
					quote = 0;
			}
			if (*str != c || quote)
			{
				count++;
				while (*str && (*str != c || quote))
				{
					if (*str == '\'' || *str == '\"')
					{
						if (quote == 0)
							quote = *str;
						else if (quote == *str)
							quote = 0;
					}
					str++;
				}
			}
		}
		else
			str++;
	}
	return (count);
}

char	**ft_mini_split(const char *s, char c)
{
	int		i;
	int		j;
	int		k;
	int		quote;
	char	**dest;

	i = 0;
	j = 0;
	quote = 0;
	dest = (char **)malloc(sizeof(char *) * (ft_count_words(s, c) + 1));
	if (!dest)
		return (NULL);
	while (s[i])
	{
		if (s[i] != c || quote)
		{
			k = 0;
			if (s[i] == '\'' || s[i] == '\"')
			{
				quote = s[i];
				k++;
			}
			while (s[i + k] && (s[i + k] != c || quote))
			{
				if (s[i + k] == quote)
				{
					k++;
					quote = 0;
					break ;
				}
				k++;
			}
			dest[j++] = ft_substr(s, i, k);
			i += k;
		}
		else
			i++;
	}
	dest[j] = NULL;
	return (dest);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		++i;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
