/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muguveli <muguveli@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 14:46:10 by muguveli          #+#    #+#             */
/*   Updated: 2024/07/05 18:25:04 by muguveli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

static unsigned int	in_array(const char *str, char d)
{
	unsigned int	i;

	i = 0;
	while (*str)
	{
		if (*str == d)
			str++;
		else
		{
			while (*str != d && *str)
				str++;
			i++;
		}
	}
	return (i);
}

char	**ft_split(char const *s, char c)
{
	char			**str;
	unsigned int	j;
	unsigned int	a;

	if (!s)
		return (0);
	str = (char **)ft_calloc(in_array(s, c) + 1, sizeof(char *));
	if (!str)
		return (0);
	a = 0;
	while (*s)
	{
		if (*s == c)
			s++;
		else
		{
			j = 0;
			while (*s != c && *s && ++j)
				s++;
			str[++a - 1] = (char *)ft_calloc(j + 1, sizeof(char));
			ft_strlcpy(str[a - 1], s - j, j + 1);
		}
	}
	return (str);
}
