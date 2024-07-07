/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muguveli <muguveli@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 00:40:49 by halozdem          #+#    #+#             */
/*   Updated: 2024/07/07 15:48:24 by muguveli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "stdio.h"
#include "stdlib.h"

int	main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	t_minishell	*minishell;

	minishell = malloc(sizeof(t_minishell));
	if (!minishell)
		return (EXIT_FAILURE); //hata mesajı
	parse_env(minishell, env);
	while (1)
	{
		minishell->line = readline("minishell> ");
		if (ft_strlen(minishell->line) != 0)
			add_history(minishell->line);
		// if(!parser(minishell))
		// 	lexer(minishell); // lexer parserin içine taşıncak ve bu kısıma executor gelcek.
	}
	return (EXIT_SUCCESS);
}
