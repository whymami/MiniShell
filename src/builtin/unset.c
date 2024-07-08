/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btanir <btanir@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 18:57:09 by halozdem          #+#    #+#             */
/*   Updated: 2024/07/08 16:10:07 by btanir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void *del(void *content)
{
	if (content)
		free(content);
	return NULL;
}

void unset(t_minishell *mini, char *key)
{
	t_dlist *lst;

	lst = search_env(mini, key);
	if (lst)
		dlist_delone(lst, (void(*))del);
}
