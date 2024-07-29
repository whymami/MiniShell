/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btanir <btanir@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 10:46:21 by eyasa             #+#    #+#             */
/*   Updated: 2024/07/29 17:59:46 by btanir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "stdio.h"
#include "stdlib.h"

void	init_data(t_minishell *minishell)
{
	minishell->line = NULL;
	minishell->pipe_count = 0;
	minishell->hrd_cmd = NULL;
	minishell->pipe_fd = NULL;
	minishell->pid = NULL;
	minishell->oldpwd = NULL;
	minishell->tokens = NULL;
	minishell->env = NULL;
	minishell->args = NULL;
	minishell->exit_code = 0;
	minishell->g_fd.change = 0;
}

int	shell_loop(t_minishell *minishell)
{
	while (1)
	{
		minishell->line = readline("minishell> ");
		if (minishell->line == NULL)
		{
			ft_putstr_fd("exit\n", 0);
			exit(0);
		}
		if (ft_strlen(minishell->line) != 0)
		{
			add_history(minishell->line);
			if (!parser(minishell))
			{
				dollar(minishell, 0);
				lexer(minishell);
				if (cpy_arg(minishell))
					return (FAILURE);
				if (minishell->hrd_count > 0)
					if (heredoc(minishell))
						continue ;
				execute_command(minishell);
			}
		}
	}
	return (SUCCESS);
}

int	main(int argc, char **argv, char **env)
{
	t_minishell	*minishell;

	(void)argc;
	(void)argv;
	minishell = malloc(sizeof(t_minishell));
	if (!minishell)
		return (ft_putstr_fd("Error: Memory allocation error\n", 2),
			EXIT_FAILURE);
	init_data(minishell);
	signal(SIGINT, signal_handler);
	parse_env(minishell, env);
	shell_loop(minishell);
	return (SUCCESS);
}
