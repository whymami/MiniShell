/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btanir <btanir@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 18:55:17 by halozdem          #+#    #+#             */
/*   Updated: 2024/07/08 16:14:36 by btanir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	export(t_minishell *minishell, char *key, char *value)
{
	t_env	*env_data;
	t_dlist	*new;

	env_data = malloc(sizeof(env_data));
	env_data->key = key;
	env_data->value = value;
	new = dlist_new(env_data);
	dlist_add_back(&minishell->env, new);
}
