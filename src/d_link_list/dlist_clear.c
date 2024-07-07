/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlist_clear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btanir <btanir@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 14:49:06 by muguveli          #+#    #+#             */
/*   Updated: 2024/07/06 20:23:03 by btanir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	dlinked_list_clear(t_dlinked_list **lst, void (*del)(void *))
{
	t_dlinked_list	*tmp;

	if (!lst || !*lst)
		return ;
	while (*lst)
	{
		tmp = (*lst)->next;
		dlist_delone(*lst, del);
		*lst = tmp;
	}
	*lst = NULL;
}
