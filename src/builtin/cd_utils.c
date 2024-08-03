/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyasa <eyasa@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 13:53:36 by eyasa             #+#    #+#             */
/*   Updated: 2024/08/03 14:08:20 by eyasa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	change_oldpwd(t_dlist *oldpwd_env, t_dlist *pwd_env, char *value)
{
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
}

void	change_pwd(t_minishell *mini, char *pwd)
{
	t_dlist	*pwd_env;
	t_dlist	*oldpwd_env;
	char	*value;

	pwd_env = search_env(mini, "PWD");
	oldpwd_env = search_env(mini, "OLDPWD");
	value = NULL;
	change_oldpwd(oldpwd_env, pwd_env, value);
	if (pwd_env)
	{
		if (!oldpwd_env)
			dlist_add_back(&mini->env, dlist_new(ft_strjoin("OLDPWD=",
						mini->oldpwd)));
		free(pwd_env->data);
		pwd_env->data = ft_strjoin("PWD=", pwd);
	}
}
