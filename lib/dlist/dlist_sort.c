/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlist_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyasa <eyasa@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 19:42:32 by eyasa             #+#    #+#             */
/*   Updated: 2024/07/20 19:45:57 by eyasa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	dlist_sort(t_dlist **head, int (*cmp)(const char *, const char *,
			size_t))
{
	t_dlist *i;
	int swapped;

	if (!head || !*head)
		return ;
	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		i = *head;
		while (i->next)
		{
			if (cmp(i->data, i->next->data, ft_strlen(i->next->data)) > 0)
			{
				dlist_swap(i, i->next);
				swapped = 1;
			}
			i = i->next;
		}
	}
}