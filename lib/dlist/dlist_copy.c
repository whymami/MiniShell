/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlist_copy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyasa <eyasa@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 13:32:57 by eyasa             #+#    #+#             */
/*   Updated: 2024/07/20 19:40:46 by eyasa            ###   ########.fr       */
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
