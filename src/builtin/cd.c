/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyasa <eyasa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 16:48:57 by eyasa             #+#    #+#             */
/*   Updated: 2024/07/11 18:13:03 by eyasa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	get_target_directory(t_minishell *mini, char *av, char **target_dir)
{
	t_dlist	*path;
	t_env	*env_data;

	path = NULL;
	env_data = NULL;
	if (!av || ft_strncmp(av, "~", 1) == 0)
		path = search_env(mini, "HOME");
	else if (ft_strncmp(av, "-", 1) == 0)
	{
		path = search_env(mini, "OLDPWD");
		if (!path)
			return (ft_printf("OLDPWD not set\n"), EXIT_FAILURE);
	}
	if (path)
	{
		env_data = (t_env *)(path->data);
		if (!env_data || !env_data->value)
			return (ft_printf("Invalid environment data\n"), EXIT_FAILURE);
		*target_dir = env_data->value;
	}
	else
		*target_dir = av;
	return (EXIT_SUCCESS);
}

int	cd(t_minishell *mini, char *av)
{
	char	*target_dir;
	int		err;

	err = get_target_directory(mini, av, &target_dir);
	if (err == EXIT_FAILURE)
		return (EXIT_FAILURE);
	err = chdir(target_dir);
	if (err == -1)
		return (ft_printf("minishell: cd: %s: No such file or directory\n", target_dir),
			EXIT_FAILURE);
	if (av && ft_strncmp(av, "-", 1) == 0)
	{
		// target_dir = ((t_env *)search_env(mini, "PWD")->data)->value;
		// env_data = search_env(mini, "OLDPWD")->data;
		// free(env_data->value);
		// env_data->value = target_dir;
		free(target_dir);
		target_dir = ft_strdup(get_pwd());
	}
	return (EXIT_SUCCESS);
}
