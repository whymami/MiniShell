/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btanir <btanir@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 00:40:49 by halozdem          #+#    #+#             */
/*   Updated: 2024/07/18 19:15:52 by btanir           ###   ########.fr       */
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
	parse_env(minishell, env);
	while (1)
	{
		minishell->line = readline("minishell> ");
		if (minishell->line && ft_strlen(minishell->line) != 0)
		{
			add_history(minishell->line);
			if (!parser(minishell))
			{
				if (!heredoc(minishell))
				{
					dollar(minishell, &minishell->line);
					lexer(minishell);
					execute_command(minishell);
				}
			}
		}
	}
	return (SUCCESS);
}
