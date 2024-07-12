/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyasa <eyasa@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 13:20:14 by muguveli          #+#    #+#             */
/*   Updated: 2024/07/12 17:23:36 by eyasa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <sys/wait.h>

static char	**cpy_arg(t_minishell *minishell)
{
	t_dlist	*temp;
	char	**argv;
	int		i;

	temp = minishell->tokens;
	i = 0;
	argv = malloc(sizeof(char *) * (dlist_size(minishell->tokens) + 1));
	while (temp)
	{
		argv[i++] = strdup(temp->data);
		temp = temp->next;
	}
	argv[i] = NULL;
	return (argv);
}

void	get_cmd(char **argv, char **cmd, char ***args)
{
	char	**tmp_argv;
	int		count;
	int		i;

	tmp_argv = ft_split(argv[0], ' ');
	*cmd = tmp_argv[0];
	count = 0;
	i = -1;
	while (tmp_argv[count])
		count++;
	*args = malloc(sizeof(char *) * (count + 1));
	(*args)[0] = tmp_argv[0];
	while (++i < count)
		(*args)[i] = tmp_argv[i];
	(*args)[count] = NULL;
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
		return (NULL);
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
	return (NULL);
}

char **env(t_minishell *minishell)
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

int check_bultin (t_minishell *minishell, char *cmd, char **args)
{
	ft_printf("args: %s\n", args[0]);
	if (ft_strncmp(cmd, "env", 3) == 0)
		print_env(minishell);
	else if (ft_strncmp(cmd, "export", 6) == 0)
		export(minishell, args[1]);
	else if (ft_strncmp(cmd, "unset", 5) == 0)
		unset(minishell, args[1]);
	else if (ft_strncmp(cmd, "cd", 2) == 0)
		cd(minishell, args[1]);
	else if (ft_strncmp(cmd, "echo", 4) == 0)
		echo(args);
	else if (ft_strncmp(cmd, "exit", 4) == 0)
		ft_exit(minishell, args[1]);
	else
		return (0);
	return (1);
}

void	execute_command(t_minishell *minishell)
{
	char	**argv;
	char	**envs;
	char	*cmd;
	char	**args;
	pid_t	pid;
	int		status;
	char	*path;

	argv = cpy_arg(minishell);
	get_cmd(argv, &cmd, &args);
	if (check_bultin(minishell, cmd, args) == 1)
		return ;
	path = find_path(minishell, cmd);

	pid = fork();
	envs = env(minishell);
	if (pid == 0)
	{
		if (execve(path, args, envs) == -1)
			perror("execve failed");
	}
	else
		waitpid(pid, &status, 0);
}
