/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halozdem <halozdem@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 13:37:13 by halozdem          #+#    #+#             */
/*   Updated: 2024/07/07 19:41:53 by halozdem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static t_env	*parse_equals(char *env)
{
	int		y;
	t_env	*env_data;
	int		flag;

	flag = 0;
	y = -1;
	env_data = malloc(sizeof(env_data));
	while (env[++y])
	{
		if (flag == 0 && env[y] == '=')
		{
			env_data->key = ft_substr(env, 0, y);
			flag = 1;
		}
		else if (flag == 1)
		{
			env_data->value = ft_substr(env, y, ft_strlen(env) - y);
			break ;
		}
	}
	return (env_data);
}

t_dlist	*search_env(t_minishell *minishell, char *key)
{
	t_dlist	*tmp;

	tmp = minishell->env;
	while (tmp)
	{
		if (ft_strnstr(((t_env *)tmp->data)->key, key, ft_strlen(key)))
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

void	print_env(t_minishell *minishell)
{
	t_dlist	*env_data;

	env_data = minishell->env;
	while (env_data)
	{
		ft_printf("%s=%s\n", ((t_env *)env_data->data)->key,
			((t_env *)env_data->data)->value);
		env_data = env_data->next;
	}
}

void	parse_env(t_minishell *minishell, char **env)
{
	int	i;

	i = 0;
	minishell->env = dlist_new(parse_equals(env[0]));
	while (env[++i])
		dlist_add_back(&minishell->env, ft_lstnew(parse_equals(env[i])));


}
