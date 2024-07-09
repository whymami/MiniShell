/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlist_size.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muguveli <muguveli@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 20:37:00 by muguveli          #+#    #+#             */
/*   Updated: 2024/07/09 20:39:19 by muguveli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/dlist.h"

int	dlist_size(t_dlist *lst)
{
	int i;
	t_dlist *tmp;

	i = 0;
	tmp = lst;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}