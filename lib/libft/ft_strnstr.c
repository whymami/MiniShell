/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muguveli <muguveli@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 13:40:45 by muguveli          #+#    #+#             */
/*   Updated: 2024/07/05 18:25:04 by muguveli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

char	*ft_strnstr(const char *src, const char *dest, size_t n)
{
	if (*dest == '\0')
		return ((char *)src);
	while (*src && n-- >= ft_strlen(dest))
	{
		if ((*src == *dest) && (ft_strncmp(src, dest, ft_strlen(dest)) == 0))
			return ((char *)src);
		src++;
	}
	return (NULL);
}
