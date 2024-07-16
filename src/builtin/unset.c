/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muguveli <muguveli@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 18:57:09 by halozdem          #+#    #+#             */
/*   Updated: 2024/07/14 03:20:48 by muguveli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	unset(t_minishell *mini, char **key)
{
	t_dlist	*lst;
	int		i;

	i = -1;
	while (key[++i])
	{
		lst = search_env(mini, key[i]);
		if (lst)
			dlist_delone(lst, del);
	}
}
