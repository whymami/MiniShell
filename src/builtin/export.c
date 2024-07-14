/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muguveli <muguveli@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 18:55:17 by halozdem          #+#    #+#             */
/*   Updated: 2024/07/14 04:34:28 by muguveli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	export(t_minishell *minishell, char *env_data)
{
	t_dlist	*new;
	int		i;

	if (!env_data)
	{
		new = minishell->env;
		while (new &&ft_printf("declare -x %s\n", new->data))
			new = new->next;
		return ;
	}
	i = -1;
	while (env_data[++i])
		if (env_data[i] == '=')
			break ;
	if (env_data[i] && env_data[i - 1] && env_data[i - 1] == ' ' && env_data[i
		+ 1] && env_data[i + 1] == ' ')
		return ;
	dlist_add_back(&minishell->env, dlist_new(env_data));
}
