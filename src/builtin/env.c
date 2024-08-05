/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btanir <btanir@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 13:37:13 by btanir            #+#    #+#             */
/*   Updated: 2024/08/03 18:47:28 by btanir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	get_key(char *line)
{
	int	j;

	j = 0;
	while (line[j] && line[j] != '=')
		j++;
	return (j);
}

char	*get_value(char *line)
{
	int		i;
	char	*value;

	if (!line)
		return (NULL);
	i = get_key(line);
	if (!line[i])
		return (NULL);
	value = ft_strdup(line + i + 1);
	return (value);
}

t_dlist	*search_env(t_minishell *minishell, char *key)
{
	t_dlist	*tmp;
	char	*tmp_str;

	tmp = minishell->env;
	if (key != NULL && ft_strlen(key) != 0)
	{
		while (tmp)
		{
			tmp_str = ft_substr(tmp->data, 0, get_key(tmp->data));
			if (!ft_strcmp(tmp_str, key))
				return (free(tmp_str), tmp);
			free(tmp_str);
			tmp = tmp->next;
		}
	}
	return (NULL);
}

void	print_env(t_minishell *minishell)
{
	t_dlist	*env_data;

	env_data = minishell->env;
	while (env_data && printf("%s\n", (char *)env_data->data))
		env_data = env_data->next;
}

void	parse_env(t_minishell *minishell, char **env)
{
	int	i;

	i = 0;
	minishell->env = dlist_new(ft_strdup(env[i]));
	while (env[++i])
		dlist_add_back(&minishell->env, dlist_new(ft_strdup(env[i])));
}
