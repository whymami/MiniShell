/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muguveli <muguveli@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 13:20:14 by muguveli          #+#    #+#             */
/*   Updated: 2024/07/13 18:14:28 by muguveli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <sys/wait.h>

int	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
	return (SUCCESS);
}

int	cpy_arg(t_minishell *minishell, char ***cmd, char ****args)
{
	t_dlist	*tokens;
	int		i;
	int		k;

	tokens = minishell->tokens;
	i = 0;
	k = 0;
	*cmd = ft_calloc(1, sizeof(char *) * (dlist_size(minishell->tokens) + 1));
	*args = ft_calloc(1, sizeof(char **) * (dlist_size(minishell->tokens) + 1));
	while (tokens)
	{
		(*args)[i] = ft_split(tokens->data, ' ');
		(*cmd)[i] = (*args)[i][0];
		i++;
		k++;
		tokens = tokens->next;
	}	
	return (SUCCESS);
}
char	*find_path(t_minishell *minishell, char *cmd)
{
	char	*cmd_slash;
	char	*path;
	char	**path_split;
	char	*path_cmd;
	int		i;
	t_dlist	*path_list;

	cmd_slash = ft_strjoin("/", cmd);
	path_list = search_env(minishell, "PATH");
	if (!path_list)
		return (cmd);
	path = path_list->data;
	path_split = ft_split(path + 5, ':');
	i = 0;
	while (path_split[i])
	{
		path_cmd = ft_strjoin(path_split[i], cmd_slash);
		if (access(path_cmd, F_OK) == 0)
		{
			free(cmd_slash);
			return (path_cmd);
		}
		free(path_cmd);
		i++;
	}
	free(cmd_slash);
	return (cmd);
}

char	**env(t_minishell *minishell)
{
	t_dlist	*env_data;
	char	**env;
	int		i;

	env_data = minishell->env;
	i = 0;
	env = ft_calloc(1, sizeof(char *) * (dlist_size(minishell->env) + 1));
	while (env_data)
	{
		env[i++] = env_data->data;
		env_data = env_data->next;
	}
	env[i] = NULL;
	return (env);
}

int	check_bultin(t_minishell *minishell, char **cmd, char ***args, int *i)
{
	if (ft_strncmp(cmd[*i], "env", 3) == 0)
		print_env(minishell);
	else if (ft_strncmp(cmd[*i], "export", 6) == 0)
		export(minishell, *args[*i]);
	else if (ft_strncmp(cmd[*i], "unset", 5) == 0)
		unset(minishell, *args[*i]);
	else if (ft_strncmp(cmd[*i], "cd", 2) == 0)
		cd(minishell, *args[*i]);
	else if (ft_strncmp(cmd[*i], "echo", 4) == 0)
		echo(args[*i]);
	else if (ft_strncmp(cmd[*i], "exit", 4) == 0)
		ft_exit(minishell, *args[*i]);
	else
		return (0);
	return (1);
}

int	create_fork(t_minishell *minishell, char **cmd, char ***args, int *i)
{
	pid_t	pid;
	int		status;
	char	**envs;
	char	*path;

	path = find_path(minishell, cmd[*i]);
	pid = fork();
	envs = env(minishell);
	if (pid == 0)
	{
		if (execve(path, args[*i], envs) == -1)
			return (perror("execve: "), FAILURE);
	}
	else
		waitpid(pid, &status, 0);
	return (SUCCESS);
}

int	single_command(t_minishell *minishell)
{
	char	**cmd;
	char	***args;
	int		i;

	i = 0;
	if (cpy_arg(minishell, &cmd, &args))
		return (FAILURE);
	if (check_bultin(minishell, cmd, args, &i) == 1)
		return (SUCCESS);
	if (create_fork(minishell, cmd, args, &i))
		return (FAILURE);
	return (SUCCESS);
}

int	execute_command(t_minishell *minishell)
{
	if (minishell->pipe_count == 0)
		return (single_command(minishell));
	else
		return (multiple_command(minishell));
	return (FAILURE);
}
