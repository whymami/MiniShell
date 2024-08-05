/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btanir <btanir@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 19:24:46 by muguveli          #+#    #+#             */
/*   Updated: 2024/08/03 18:50:05 by btanir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**my_realloc(char **ptr, size_t size)
{
	char	**new_ptr;

	new_ptr = (char **)malloc(size * sizeof(char *));
	if (!new_ptr)
	{
		printf("reallocation failed!\n");
		free(ptr);
		exit(EXIT_FAILURE);
	}
	if (ptr)
	{
		ft_memcpy(new_ptr, ptr, size);
		free(ptr);
	}
	return (new_ptr);
}
