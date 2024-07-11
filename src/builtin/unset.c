/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muguveli <muguveli@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 18:57:09 by halozdem          #+#    #+#             */
/*   Updated: 2024/07/11 16:10:10 by muguveli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	unset(t_minishell *mini, char *key)
{
	t_dlist	*lst;

	if (!key)
		return ;
	lst = search_env(mini, key);
	if (lst)
		dlist_delone(lst, del);
}
