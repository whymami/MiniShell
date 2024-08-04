/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btanir <btanir@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 14:31:12 by muguveli          #+#    #+#             */
/*   Updated: 2024/08/03 18:48:55 by btanir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	handle_token(t_dlist *tokens, char ***args, char ***args_with_quotes, int i)
{
	char	*line;

	line = ft_strdup(tokens->data);
	if (!line)
		return (perror("ft_strdup"), free_args(args), FAILURE);
	if (replace_arg(&line))
		return (FAILURE);
	args[i] = ft_mini_split(line, ' ');
	if (!args[i])
		return (perror("ft_mini_split"), free(line), FAILURE);
	args_with_quotes[i] = ft_mini_split(line, ' ');
	if (!args_with_quotes[i])
		return (free_args(args_with_quotes), free(line),
			perror("ft_mini_split"), FAILURE);
	free(line);
	return (SUCCESS);
}

int	cpy_arg(t_minishell *minishell)
{
	t_dlist	*tokens;
	int		i;
	char	***args;

	tokens = minishell->tokens;
	i = 0;
	args = ft_calloc(1, sizeof(char **) * (dlist_size(minishell->tokens) + 1));
	if (!args)
		return (perror("ft_calloc"), FAILURE);
	minishell->args_with_quotes = ft_calloc(1, sizeof(char **)
			* (dlist_size(minishell->tokens) + 1));
	if (!minishell->args_with_quotes)
		return (free_args(args), perror("ft_calloc"), FAILURE);
	while (tokens)
	{
		if (handle_token(tokens, args, minishell->args_with_quotes, i))
			return (free_args(args), FAILURE);
		i++;
		tokens = tokens->next;
	}
	minishell->args = args;
	return (SUCCESS);
}

char	*search_path(char **path_split, char *temp, t_minishell *minishell)
{
	int		i;
	char	*path_cmd;

	i = -1;
	while (path_split[++i])
	{
		path_cmd = ft_strjoin(path_split[i], temp);
		if (access(path_cmd, F_OK) == 0)
		{
			free_split(path_split);
			free(temp);
			minishell->sign = 1;
			return (path_cmd);
		}
		free(path_cmd);
	}
	return (NULL);
}

char	*find_path(t_minishell *minishell, char *cmd)
{
	char	*temp;
	char	**path_split;
	t_dlist	*path_list;
	char	*path_cmd;

	temp = ft_strjoin("/", cmd);
	path_list = search_env(minishell, "PATH");
	if (!path_list)
	{
		minishell->sign = 0;
		return (free(temp), cmd);
	}
	path_split = ft_split(path_list->data + 5, ':');
	path_cmd = search_path(path_split, temp, minishell);
	if (path_cmd != NULL)
		return (path_cmd);
	free_split(path_split);
	minishell->sign = 0;
	return (free(temp), cmd);
}

char	**env(t_minishell *minishell)
{
	t_dlist	*env_data;
	char	**env;
	int		i;

	env_data = minishell->env;
	i = 0;
	env = ft_calloc(1, sizeof(char *) * (dlist_size(minishell->env) + 1));
	if (!env)
		return (perror("malloc"), NULL);
	while (env_data)
	{
		env[i++] = env_data->data;
		env_data = env_data->next;
	}
	env[i] = NULL;
	return (env);
}
