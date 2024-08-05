/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlist_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btanir <btanir@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 19:42:32 by muguveli          #+#    #+#             */
/*   Updated: 2024/08/03 18:45:21 by btanir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	dlist_sort(t_dlist **head, int (*cmp)(char *, char *))
{
	t_dlist	*i;
	int		swapped;

	if (!head || !*head)
		return ;
	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		i = *head;
		while (i->next)
		{
			if (cmp(i->data, i->next->data) > 0)
			{
				dlist_swap(i, i->next);
				swapped = 1;
			}
			i = i->next;
		}
	}
}
