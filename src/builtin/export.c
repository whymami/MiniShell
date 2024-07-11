/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btanir <btanir@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 18:55:17 by halozdem          #+#    #+#             */
/*   Updated: 2024/07/11 15:35:58 by btanir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	export(t_minishell *minishell, char *env_data)
{
	t_dlist	*new;

	new = dlist_new(env_data);
	dlist_add_back(&minishell->env, new);
}
