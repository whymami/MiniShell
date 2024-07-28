/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btanir <btanir@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 16:48:47 by eyasa             #+#    #+#             */
/*   Updated: 2024/07/27 14:31:29 by btanir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_str_digit(char *str)
{
	if (str[0] == '-' || str[0] == '+')
		str++;
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

void	ft_exit(t_minishell *mini, char **av)
{
	int	exit_code;
	int	i;
	i = 0;
	while (av[i])
		i++;
	exit_code = 0;
	ft_putstr_fd("exit\n", STD_OUTPUT);
	free_minishell(mini);
	if (i > 2)
	{
		ft_putstr_fd(" too many arguments\n", STDERR_FILENO);
		exit_code = 1;
	}
	else if (av[1] != NULL)
	{
		if (is_str_digit(av[1]))
			exit_code = ft_atoi(av[1]);
		else
		{
			ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
			ft_putstr_fd(av[1], STDERR_FILENO);
			ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
			exit_code = 255;
		}
	}
	else
		exit_code = 0;
	exit(exit_code);
}
