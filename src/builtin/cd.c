/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyasa <eyasa@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 16:48:57 by eyasa             #+#    #+#             */
/*   Updated: 2024/08/03 13:23:18 by eyasa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	change_pwd(t_minishell *mini, char *pwd)
{
	t_dlist	*pwd_env;
	t_dlist	*oldpwd_env;
	char	*value;

	pwd_env = search_env(mini, "PWD");
	oldpwd_env = search_env(mini, "OLDPWD");
	value = NULL;
	if (oldpwd_env && pwd_env)
	{
		value = get_value(pwd_env->data);
		if (value)
		{
			free(oldpwd_env->data);
			oldpwd_env->data = ft_strjoin("OLDPWD=", value);
			free(value);
		}
	}
	if (pwd_env)
	{
		if (!oldpwd_env)
		{
			char *oldpwd_str = ft_strjoin("OLDPWD=", mini->oldpwd);
			dlist_add_back(&mini->env, dlist_new(oldpwd_str));
			free(oldpwd_str);
			if (mini->oldpwd)
				free(mini->oldpwd);
		}
		free(pwd_env->data);
		pwd_env->data = ft_strjoin("PWD=", pwd);
	}
}

static int	check_meta(char *av, t_minishell *mini, t_dlist **path)
{
	if (!av || ft_strncmp(av, "~", 1) == 0)
	{
		if (av && ft_strncmp(av, "~~", 2) == 0)
			return (err_msg("cd: ", av, ": No such file or directory"),
				mini->exit_code = 1, FAILURE);
		*path = search_env(mini, "HOME");
		if (!(*path))
			return (err_msg("cd: ", NULL, "Home not set"), mini->exit_code = 1,
				FAILURE);
	}
	else if (ft_strncmp(av, "-", 1) == 0)
	{
		*path = search_env(mini, "OLDPWD");
		if (!(*path))
			return (err_msg("cd: ", NULL, "OLDPWD not set"),
				mini->exit_code = 1, FAILURE);
	}
	return (SUCCESS);
}

static int	get_target_directory(t_minishell *mini, char *av, char **target_dir)
{
	t_dlist	*path;
	char	*env_data;

	path = NULL;
	env_data = NULL;
	if (check_meta(av, mini, &path))
		return (FAILURE);
	if (path)
	{
		env_data = get_value(path->data);
		if (!env_data)
			return (err_msg("cd: ", NULL, " No such file or directory"),
				mini->exit_code = 1, FAILURE);
		*target_dir = env_data;
	}
	else if (av)
		*target_dir = av;
	return (SUCCESS);
}

int	cd(t_minishell *mini, char *av)
{
	char	*target_dir;
	int		err;
	char	pwd[4096];
	char	*oldpwd_copy;

	if (!getcwd(pwd, 4096))
		return (err_msg("cd: ", NULL, "Getcwd error"), EXIT_FAILURE);
	oldpwd_copy = ft_strdup(pwd);
	if (!oldpwd_copy)
		return (err_msg("cd: ", NULL, "OLDPWD not set."), EXIT_FAILURE);
	if (mini->oldpwd)
		free(mini->oldpwd);
	mini->oldpwd = oldpwd_copy;
	err = get_target_directory(mini, av, &target_dir);
	if (err == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (chdir(target_dir) == -1)
		return (perror("minishell: cd"),
			mini->exit_code = 1, EXIT_FAILURE);
	if (!getcwd(pwd, 4096))
		return (err_msg("cd: ", NULL, "Getcwd error"), EXIT_FAILURE);
	change_pwd(mini, pwd);
	if (av && ft_strncmp(av, "-", 1) == 0)
		printf("%s\n", pwd);
	if (target_dir != av)
		free(target_dir);
	return (EXIT_SUCCESS);
}
