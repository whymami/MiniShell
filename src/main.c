/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btanir <btanir@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 00:40:49 by btanir            #+#    #+#             */
/*   Updated: 2024/07/14 17:44:41 by btanir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "stdio.h"
#include "stdlib.h"

int main(int argc, char **argv, char **env)
{
	t_minishell *minishell;

	(void)argc;
	(void)argv;
	minishell = ft_calloc(1, sizeof(t_minishell));
	if (!minishell)
		return (ft_putstr_fd("Error: Memory allocation error\n", 2), EXIT_FAILURE); // hata mesaj
	parse_env(minishell, env);
	while (1)
	{
		minishell->line = readline("minishell> ");
		// signal(SIGINT, signal_handler);
		if (ft_strlen(minishell->line) != 0)
		{
			add_history(minishell->line);
			if (!parser(minishell))
			{
				lexer(minishell);
				execute_command(minishell);
			}
		}
	}
	return (SUCCESS);
}
