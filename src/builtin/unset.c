/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyasa <eyasa@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 00:22:45 by eyasa             #+#    #+#             */
/*   Updated: 2024/07/21 00:22:47 by eyasa            ###   ########.fr       */
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
		if (!ft_strncmp(key[i], "_", 1))
			continue ;
		lst = search_env(mini, key[i]);
		if (lst)
			dlist_delone(lst, del);
	}
}
