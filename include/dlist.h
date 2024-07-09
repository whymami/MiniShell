/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlist.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muguveli <muguveli@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 18:00:25 by muguveli          #+#    #+#             */
/*   Updated: 2024/07/09 20:38:13 by muguveli         ###   ########.fr       */
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
void				dlist_delone(t_dlist *lst, void (*del)(void *));
int					dlist_size(t_dlist *lst);

#endif