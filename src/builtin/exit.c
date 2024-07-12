/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyasa <eyasa@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 16:48:47 by eyasa             #+#    #+#             */
/*   Updated: 2024/07/12 17:26:44 by eyasa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_str_digit(char *str)
{
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

void	free_minishell(t_minishell *mini)
{
	t_dlist	*tmp;

	while (mini->env)
	{
		tmp = mini->env;
		mini->env = mini->env->next;
		free(tmp->data);
		free(tmp);
	}
	free(mini->oldpwd);
	free(mini->line);
	while (mini->tokens)
	{
		tmp = mini->tokens;
		mini->tokens = mini->tokens->next;
		free(tmp->data);
		free(tmp);
	}
	free(mini);
}

void	ft_exit(t_minishell *mini, char *av)
{
	int	exit_code;

	exit_code = 0;
	ft_putstr_fd("exit\n", STDERR_FILENO);
	free_minishell(mini);
	if (av)
	{
		if (is_str_digit(av))
			exit_code = ft_atoi(av);
		else
		{
			ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
			ft_putstr_fd(av, STDERR_FILENO);
			ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
			exit_code = 255;
		}
	}
	else
		exit_code = 0;
	exit(exit_code);
}
