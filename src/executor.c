/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btanir <btanir@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 13:20:14 by muguveli          #+#    #+#             */
/*   Updated: 2024/07/23 10:51:27 by btanir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <dirent.h>
#include <sys/wait.h>

t_fd	g_fd;

void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

int	cpy_arg(t_minishell *minishell, char ***cmd, char ****args)
{
	t_dlist	*tokens;
	int		i;

	(void)cmd;
	tokens = minishell->tokens;
	i = 0;
	*args = ft_calloc(1, sizeof(char **) * (dlist_size(minishell->tokens) + 1));
	while (tokens)
	{
		(*args)[i] = ft_mini_split(tokens->data, ' ');
		i++;
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
	i = -1;
	while (path_split[++i])
	{
		path_cmd = ft_strjoin(path_split[i], cmd_slash);
		if (access(path_cmd, F_OK) == 0)
			return (free_split(path_split), free(cmd_slash), path_cmd);
		free(path_cmd);
	}
	free_split(path_split);
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
	if (ft_strcmp(cmd[*i], "env") == 0)
		print_env(minishell);
	else if (ft_strcmp(cmd[*i], "export") == 0)
		export(minishell, (*args));
	else if (ft_strcmp(cmd[*i], "pwd") == 0)
		get_pwd();
	else if (ft_strcmp(cmd[*i], "unset") == 0)
		unset(minishell, (*args));
	else if (ft_strcmp(cmd[*i], "cd") == 0)
		cd(minishell, (*args)[1]);
	else if (ft_strcmp(cmd[*i], "echo") == 0)
		echo(args[*i]);
	else if (ft_strcmp(cmd[*i], "exit") == 0)
		ft_exit(minishell, (*args)[1]);
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
	char	*err;

	if (ft_strncmp(cmd[*i], "./", 2) != 0)
		path = find_path(minishell, cmd[*i]);
	else
		path = cmd[*i];
	pid = fork();
	envs = env(minishell);
	if (pid == 0)
	{
		if (execve(path, args[*i], envs) == -1)
		{
			err = ft_strjoin("minishell: ", cmd[*i]);
			return (perror(err), free(err), exit(1), FAILURE);
		}
	}
	else
	{
		waitpid(pid, &status, 0);
		dup2(g_fd.std_in, STD_OUTPUT);
		dup2(g_fd.std_out, STD_INPUT);
		g_fd.change = 0;
	}
	return (SUCCESS);
}

void	remove_quotes(char ***args)
{
	char	*tmp;
	char	*tmp2;
	int		quote;
	char	*new_tmp;

	int i, j, k;
	i = -1;
	while (args[++i])
	{
		j = -1;
		while (args[i][++j])
		{
			k = -1;
			tmp = strdup(""); // Her kelime için tmp'yi başlat
			if (!tmp)
			{
				// Bellek ayrımı başarısız oldu, işlem durduruluyor
				return ;
			}
			tmp2 = args[i][j];
			quote = 0;
			while (args[i][j][++k])
			{
				if (quote == 0 && (args[i][j][k] == '\''
						|| args[i][j][k] == '\"'))
				{
					quote = args[i][j][k];
				}
				else if (quote != 0 && quote == args[i][j][k])
				{
					quote = 0;
				}
				else
				{
					new_tmp = ft_strjoin_char(tmp, args[i][j][k]);
					if (!new_tmp)
					{
						// Bellek ayrımı başarısız oldu, işlem durduruluyor
						free(tmp);
						return ;
					}
					tmp = new_tmp;
				}
			}
			args[i][j] = tmp;
			free(tmp2);
		}
	}
}

int	single_command(t_minishell *minishell)
{
	char	**cmd;
	char	***args;
	int		i;
	int		a;
	int		b;

	i = 0;
	if (cpy_arg(minishell, &cmd, &args))
		return (FAILURE);
	check_direct(minishell, args[i]);
	cmd = ft_calloc(1, sizeof(char *) * (dlist_size(minishell->tokens) + 1));
	remove_quotes(args);
	a = 0;
	b = 0;
	while (args[a])
	{
		if (args[a][0])
		{
			cmd[b] = args[a][0];
			b++;
		}
		a++;
	}
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
