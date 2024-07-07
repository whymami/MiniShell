/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlist_delone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halozdem <halozdem@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 18:16:33 by muguveli          #+#    #+#             */
/*   Updated: 2024/07/07 14:37:14 by halozdem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	dlist_delone(t_dlinked_list *lst, void (*del)(void *))
{
	if (!lst || !del)
		return ;
	del(lst->data);
	free(lst);
}
