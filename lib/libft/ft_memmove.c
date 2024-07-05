/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muguveli <muguveli@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 18:47:45 by muguveli          #+#    #+#             */
/*   Updated: 2024/07/05 18:25:04 by muguveli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

void	*ft_memmove(void *dest, const void *src, size_t len)
{
	size_t		i;
	char		*dest1;
	const char	*src1;

	i = -1;
	dest1 = (char *)dest;
	src1 = (const char *)src;
	if (!dest && !src)
		return (0);
	if (dest1 < src1)
		while (++i < len)
			dest1[i] = src1[i];
	else if (dest1 > src1)
		while (len--)
			dest1[len] = src1[len];
	return (dest);
}
