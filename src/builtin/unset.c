/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halozdem <halozdem@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 18:57:09 by halozdem          #+#    #+#             */
/*   Updated: 2024/07/07 19:43:58 by halozdem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void *del(void *content)
{
	if (content)
		free(content);
}

void unset(t_minishell *mini, char *key)
{
	t_dlist *lst;

	lst = search_env(mini, key);
	if (lst)
		dlist_delone(lst, (void(*))del);
	else
		ft_printf("key not found: %s", key);
}
