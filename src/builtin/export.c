/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halozdem <halozdem@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 18:55:17 by halozdem          #+#    #+#             */
/*   Updated: 2024/07/07 18:56:45 by halozdem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	export(t_minishell *minishell, char *key, char *value)
{
	t_env	*env_data;
	t_list	*new;

	env_data = malloc(sizeof(env_data));
	env_data->key = key;
	env_data->value = value;
	new = ft_lstnew(env_data);
	ft_lstadd_back(&minishell->env, new);
}
