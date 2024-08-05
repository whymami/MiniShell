/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlist_swap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btanir <btanir@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 19:44:50 by muguveli          #+#    #+#             */
/*   Updated: 2024/08/03 18:45:42 by btanir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	dlist_swap(t_dlist *a, t_dlist *b)
{
	void	*tmp;

	tmp = a->data;
	a->data = b->data;
	b->data = tmp;
}
