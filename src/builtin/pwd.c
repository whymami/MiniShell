/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyasa <eyasa@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 18:31:42 by halozdem          #+#    #+#             */
/*   Updated: 2024/07/09 20:30:05 by eyasa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*get_pwd(void)
{
	char	pwd[4096];
	char	*path;

	path = getcwd(pwd, 4096);
	return (ft_printf("%s\n", path), path);
}
