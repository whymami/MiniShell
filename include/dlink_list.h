/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlink_list.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muguveli <muguveli@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 18:00:25 by muguveli          #+#    #+#             */
/*   Updated: 2024/07/06 18:18:46 by muguveli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DLINK_LIST_H
# define DLINK_LIST_H

typedef struct s_dlinked_list
{
	void					*data;
	struct s_dlinked_list	*next;
	struct s_dlinked_list	*prev;
}							t_dlinked_list;

void						dlinked_list_add_back(t_dlinked_list **lst,
								t_dlinked_list *new);
void						dlinked_list_add_front(t_dlinked_list **lst,
								t_dlinked_list *new);
t_dlinked_list				*dlinked_list_new(void *data);
void						dlinked_list_clear(t_dlinked_list **lst,
								void (*del)(void *));
void						dlist_delone(t_dlinked_list *lst,
								void (*del)(void *));

#endif