/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlist.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyasa <eyasa@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 18:00:25 by muguveli          #+#    #+#             */
/*   Updated: 2024/07/20 20:03:44 by eyasa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DLIST_H
# define DLIST_H

typedef struct s_dlist
{
	void			*data;
	struct s_dlist	*next;
	struct s_dlist	*prev;
}					t_dlist;

void				dlist_add_back(t_dlist **lst, t_dlist *new);
void				dlist_add_front(t_dlist **lst, t_dlist *new);
t_dlist				*dlist_new(void *data);
void				dlist_clear(t_dlist **lst, void (*del)(void *));
t_dlist				*dlist_copy(t_dlist *lst);
void				dlist_delone(t_dlist *lst, void (*del)(void *));
int					dlist_size(t_dlist *lst);
void				dlist_sort(t_dlist **head, int (*cmp)(char *, char *));
void				dlist_swap(t_dlist *a, t_dlist *b);

#endif