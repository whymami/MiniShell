/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlist_copy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btanir <btanir@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 13:32:57 by muguveli          #+#    #+#             */
/*   Updated: 2024/08/03 18:44:45 by btanir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_dlist	*dlist_copy(t_dlist *lst)
{
	t_dlist	*new_lst;
	t_dlist	*current;
	t_dlist	*new_node;
	t_dlist	*temp;

	new_lst = NULL;
	current = lst;
	while (current)
	{
		new_node = dlist_new(current->data);
		if (!new_node)
		{
			while (new_lst)
			{
				temp = new_lst;
				new_lst = new_lst->next;
				free(temp->data);
				free(temp);
			}
			return (NULL);
		}
		dlist_add_back(&new_lst, new_node);
		current = current->next;
	}
	return (new_lst);
}
