/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btanir <btanir@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 18:55:17 by halozdem          #+#    #+#             */
/*   Updated: 2024/08/01 17:02:47 by btanir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	arg_check(char *env_data)
{
	int	i;

	i = -1;
	if (ft_isdigit(env_data[0]) || env_data[0] == '=')
		return (1);
	while (env_data[++i])
	{
		if (env_data[i] == '=')
		{
			if (env_data[i + 1] == ' ' || (i > 0 && env_data[i - 1] == ' '))
				return (1);
			break ;
		}
		if (!(isalnum(env_data[i]) || env_data[i] == '_'))
			return (1);
	}
	return (0);
}

static int	print_export(char **args, t_minishell *minishell)
{
	t_dlist	*new;
	char	*value;
	t_dlist	*temp;

	if (!args || !args[1])
	{
		new = dlist_copy(minishell->env);
		dlist_sort(&new, ft_strcmp);
		while (new)
		{
			write(1, "declare -x ", 12);
			write(1, (char *)new->data, get_key(new->data));
			value = get_value(new->data);
			if (value && write(1, "=\"", 2) && write(1, value,
					ft_strlen(value)))
				write(1, "\"", 1);
			write(1, "\n", 1);
			free(value);
			temp = new;
			new = new->next;
			free(temp);
		}
		return (FAILURE);
	}
	return (SUCCESS);
}

static void	search_to_add(t_minishell *minishell, char *arg, char *key)
{
	t_dlist	*search;

	search = search_env(minishell, key);
	if (search && ft_strncmp(search->data, arg, ft_strlen(arg)))
	{
		free(search->data);
		search->data = ft_strdup(arg);
	}
	else if (!search)
		dlist_add_back(&minishell->env, dlist_new(ft_strdup(arg)));
}

void	export(t_minishell *minishell, char **args, int *j)
{
	char	*key;
	int		i;

	if (print_export(args, minishell))
		return ;
	i = 0;
	while (args[++i])
	{
		if (arg_check(minishell->args_with_quotes[*j][i]))
		{
			ft_printf("minishell: export: `%s':", args[i]);
			ft_putstr_fd(" not a valid identifier\n", 2);
			minishell->exit_code = 1;
			continue ;
		}
		key = ft_substr(args[i], 0, get_key(args[i]));
		if (!ft_strcmp(key, "_"))
		{
			free(key);
			continue ;
		}
		search_to_add(minishell, args[i], key);
		free(key);
	}
}
