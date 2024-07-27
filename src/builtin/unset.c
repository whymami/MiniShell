/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btanir <btanir@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 00:22:45 by eyasa             #+#    #+#             */
/*   Updated: 2024/07/27 02:18:55 by btanir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	key_validation(char *key)
{
	int	i;

	i = -1;
	if (ft_isdigit(key[0]))
		return (FAILURE);
	while (key[++i])
		if (!ft_isalnum(key[i]))
			return (FAILURE);
	return (SUCCESS);
}

void	unset(t_minishell *mini, char **key)
{
	t_dlist	*lst;
	int		i;

	i = 0;
	while (key[++i])
	{
		if (key_validation(key[i]))
		{
			ft_printf("%sunset: `%s': not a valid identifier\n", ERR_TITLE,
				key[i]);
			continue ;
		}
		if (!ft_strcmp(key[i], "_"))
			continue ;
		lst = search_env(mini, key[i]);
		if (lst)
			dlist_delone(lst, del);
	}
}
