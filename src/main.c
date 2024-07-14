/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muguveli <muguveli@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 00:40:49 by halozdem          #+#    #+#             */
/*   Updated: 2024/07/14 18:37:58 by muguveli         ###   ########.fr       */
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
			// lexer parserin içine taşıncak ve bu kısıma executor gelcek.
		}
	}
	return (SUCCESS);
}
