/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btanir <btanir@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 16:48:47 by muguveli          #+#    #+#             */
/*   Updated: 2024/08/03 18:47:42 by btanir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	is_str_digit(char *str)
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

static void	free_minishell(t_minishell *mini)
{
	if (mini->env)
		dlist_clear(&mini->env, del);
	if (mini->oldpwd)
		free(mini->oldpwd);
	if (mini->line)
		free(mini->line);
	if (mini->tokens)
		dlist_clear(&mini->tokens, del);
	if (mini->args)
		free_args(mini->args);
	if (mini->args_with_quotes)
		free_args(mini->args_with_quotes);
	if (mini)
		free(mini);
}

static int	max_int(char *str)
{
	char	*number;

	if (str[0] == '-' || str[0] == '+')
		str++;
	number = ft_itoa(ft_atoi(str));
	if (ft_strcmp(number, str) != 0)
		return (free(number), 0);
	free(number);
	return (1);
}

static void	check_numeric(char *av, int *exit_code)
{
	if (is_str_digit(av) && max_int(av))
		(*exit_code) = ft_atoi(av);
	else
	{
		ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
		ft_putstr_fd(av, STDERR_FILENO);
		ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
		(*exit_code) = 255;
	}
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
	if (i > 2)
	{
		ft_putstr_fd(" too many arguments\n", STDERR_FILENO);
		exit_code = 1;
	}
	else if (av[1] != NULL)
		check_numeric(av[1], &exit_code);
	else
		exit_code = mini->exit_code;
	free_minishell(mini);
	exit(exit_code);
}
