/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlist_delone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btanir <btanir@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 18:16:33 by muguveli          #+#    #+#             */
/*   Updated: 2024/07/08 16:09:14 by btanir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void dlist_delone(t_dlist *lst, void (*del)(void *))
{
	if (!lst || !del)
        return;

    if (lst->prev)
        lst->prev->next = lst->next;
    if (lst->next)
        lst->next->prev = lst->prev;

    del(lst->data);
    free(lst);
}
