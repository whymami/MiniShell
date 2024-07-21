/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyasa <eyasa@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 18:55:17 by halozdem          #+#    #+#             */
/*   Updated: 2024/07/21 15:33:20 by eyasa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	export_check(char *env_data)
{
	int	i;

	i = -1;
	if (isdigit(env_data[0]))
		return (1);
	while (env_data[++i])
	{
		if (env_data[i] == '=')
			break ;
		if (!(isalnum(env_data[i]) || env_data[i] == '_'))
			return (1);
	}
	if (env_data[i] == '=')
	{
		if (env_data[i + 1] == ' ' || (i > 0 && env_data[i - 1] == ' '))
			return (1);
	}
	return (0);
}

void	export(t_minishell *minishell, char **env_data_list)
{
	t_dlist	*new;
	t_dlist	*search;
	int		name_length;
	char	*key;
	int		i;

	if (!env_data_list || !env_data_list[1])
	{
		new = dlist_copy(minishell->env);
		dlist_sort(&new, ft_strcmp);
		while (new)
		{
			name_length = get_key(new->data);
			ft_printf("declare -x ");
			write(1, (char *)new->data, name_length);
			write(1, "=", 1);
			printf("\"%s\"\n", get_value(new->data));
			new = new->next;
		}
		dlist_clear(&new, &del);
		return ;
	}
	i = 0;
	while (env_data_list[++i])
	{
		if (export_check(env_data_list[i]))
		{
			ft_printf("minishell: export: `%s': not a valid identifier\n",
				env_data_list[i]);
			continue ;
		}
		key = ft_substr(env_data_list[i], 0, get_key(env_data_list[i]));
		if (!ft_strncmp(key, "_", 1))
		{
			free(key);
			continue ;
		}
		search = search_env(minishell, key);
		if (search && ft_strncmp(search->data, env_data_list[i],
				ft_strlen(env_data_list[i])))
		{
			free(search->data);
			search->data = strdup(env_data_list[i]);
		}
		else if (!search)
			dlist_add_back(&minishell->env, dlist_new(env_data_list[i]));
		free(key);
	}
}
