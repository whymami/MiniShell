/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlist_delone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halozdem <halozdem@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 18:16:33 by muguveli          #+#    #+#             */
/*   Updated: 2024/07/07 19:48:34 by halozdem         ###   ########.fr       */
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
