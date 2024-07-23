/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyasa <eyasa@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 19:09:28 by eyasa             #+#    #+#             */
/*   Updated: 2024/07/23 17:47:27 by eyasa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	ft_count_words(const char *str, char c)
{
	int count;
	int quote;
	int in_word;

	count = 0;
	quote = 0;
	in_word = 0;
	while (*str)
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
			if (!in_word && (*str == '<' || *str == '>'))
			{
				count++;
				in_word = 1;
			}
		}
		else
		{
			in_word = 0;
		}
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
		while (s[i] && (s[i] == c && quote == 0))
			i++;
		k = i;
		while (s[i] && (s[i] != c || quote))
		{
			if (s[i] == '\'' || s[i] == '\"')
			{
				if (quote == 0)
					quote = s[i];
				else if (quote == s[i])
					quote = 0;
			}
			i++;
		}
		if (i > k) {
            char *substr = ft_substr(s, k, i - k);
            if (substr) {
                replace_arg(&substr);
                dest[j++] = substr;
            }
        }
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
