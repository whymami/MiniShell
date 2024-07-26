/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btanir <btanir@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 00:22:45 by eyasa             #+#    #+#             */
/*   Updated: 2024/07/26 22:46:49 by btanir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	unset(t_minishell *mini, char **key)
{
	t_dlist	*lst;
	int		i;

	i = 0;
	while (key[++i])
	{
		if (!ft_strncmp(key[i], "_", 1))
			continue ;
		lst = search_env(mini, key[i]);
		if (lst)
			dlist_delone(lst, del);
	}
}
